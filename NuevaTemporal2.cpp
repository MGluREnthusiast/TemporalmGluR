#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

vector<vector<int>> Outputfile;
vector<float> Outputtime;

// the following are the hyperparameters of the network

float Threshold = -55;
float initalWeight = 0.075;

int MOSS = 600;
int GRAN = 10000;
int GOLG = 900;
int PURK =20;
int BASK =30; //were 30
int STEL =30;
int NUCL =6;
int IO =1;
int TotalCells = MOSS+GRAN+GOLG+PURK+BASK+STEL+NUCL+IO;



float DecCund;
float DecThresh;
float DecChlor;
float VoltageLeak;

float GranulePositive = 0.00001;
float GranuleNegative = -0.00036;
float NuclearPosititve = 0.000001;
float NuclearNegative = -0.0002;

float MFActivators = 0.06;
float ThreshIncrease;
float MaxThreshold = -40;

float NuclearW;

/// The following is the number of connection
int MFtoGR = 4; /// 6 connections per about each granule cell
int MFtoGO = 20;
int MFtoNC = 100;
int GRtoGO = 100;
int GRtoPR = 8000;
int GRtoBK = 120; // were 120
int GRtoST = 120;
int GOtoGR = 3;
int PRtoNC = 15;
int PRtoBK = 0; // were 5
int BKtoPR = 5;
int STtoPR = 5;
int NCtoIO = 6;
int IOtoPR = 1;

///assuming 120 frames in 2 seconds thus each frame is 16.666 ms
/*
vector<float> TimeConstants;
TimeConstants.push_back(0.95) //MF to Go and Nu
TimeConstants.push_back(0.222) // MF to Gr
TimeConstants.push_back(0.95) // Gr to PK
TimeConstants.push_back(0.99) //Gr to Bask
TimeConstants.push_back(0.98) // Gr to Go
TimeConstants.push_back(0.333) // Go to Gr
TimeConstants.push_back(0.95) //Bask to Pk
TimeConstants.push_back(0.92) //Pk to Nu
TimeConstants.push_back(0.90) // Nu to CF
*/



vector<vector<float>> FullNetwork;
vector<vector<int>> outputs;
vector<vector<float>> weights;
int seedTimer = 0;
vector<int> MossySubset;

vector<float> PurkinjeChlorides;
vector<float> NuclearChlorides;
//////////////////////////////////////////////////////////////////////
int randGen(int min, int max){
	float timer = clock() + seedTimer;
	srand(timer);
	seedTimer++;
	return rand()%((max-1)-min + 1) + min;
	}

void InitalizeSubset(int Moss){
	for(int i = 0; i < round(Moss*MFActivators); i++){
	MossySubset.push_back(randGen(0, Moss));
}
}

void initalizeNetwork(int Moss, int Gran, int Golg, int Purk, int Bask, int Stel, int Nucl, int Io, float NucWeight){
	for (int i = 0; i < Nucl; i++){
	    NuclearChlorides.push_back(0);
	}
	for(int i = 0; i < Purk; i++){
	    PurkinjeChlorides.push_back(0);
	   }

	for(int i =0; i < Moss; i++){
		FullNetwork.push_back({0, -70, 0, Threshold, 1}); ///0 is for conductance 1 is for voltage and 2 is for weight summed stuff
    outputs.push_back({});
    weights.push_back({});
		}
	for(int i =0; i < Gran; i++){
		FullNetwork.push_back({0, -70, 0, Threshold, 2});
    outputs.push_back({});
    weights.push_back({});
		}
	for(int i =0; i < Golg; i++){
		FullNetwork.push_back({0, -70, 0, Threshold, 3});
    outputs.push_back({});
    weights.push_back({});
		}
	for(int i =0; i < Purk; i++){
		FullNetwork.push_back({0, -70, 0, Threshold, 4});
    outputs.push_back({});
    weights.push_back({});
		}
	for(int i =0; i < Bask; i++){
		FullNetwork.push_back({0, -70, 0, Threshold, 5});
    outputs.push_back({});
    weights.push_back({});
		}
	for(int i =0; i < Stel; i++){
		FullNetwork.push_back({0, -70, 0, Threshold, 6});
    outputs.push_back({});
    weights.push_back({});
		}
	for(int i =0; i < Nucl; i++){
		FullNetwork.push_back({0, -70, 0, Threshold, 7});
    outputs.push_back({});
    weights.push_back({});
		}
	for(int i = 0; i < Io; i++){
		FullNetwork.push_back({0, -70, 0, Threshold, 8});
    outputs.push_back({});
    weights.push_back({});
		}

	for(int i = 0; i < Purk; i++){ /// The true numbers are built out of the postsynaptic cell The following is for the Purkinjes
	    for (int k = 0; k < GRtoPR; k++){
	        int rand1 = randGen(Moss, Moss+Gran);
		    outputs[rand1].push_back(Moss+Gran+Golg+i);
	        weights[rand1].push_back(initalWeight);
	    }
	    for (int k = 0; k < STtoPR; k++){
	        int rand2 = randGen(Moss+Gran+Golg+Purk+Bask, Moss+Gran+Golg+Purk+Bask+Stel);
		    outputs[rand2].push_back(Moss+Gran+Golg+i);
	        weights[rand2].push_back(-initalWeight);
	    }
	    for (int k = 0; k < BKtoPR; k++){
	        int rand3 = randGen(Moss+Gran+Golg+Purk, Moss+Gran+Golg+Purk+Bask);
		    outputs[rand3].push_back(Moss+Gran+Golg+i);
	        weights[rand3].push_back(-initalWeight);
	    }
	    for (int k = 0; k < IOtoPR; k++){
		    outputs[TotalCells-1].push_back(Moss+Gran+Golg+i);
	        weights[TotalCells-1].push_back(initalWeight);
	    }
	}
	for(int i = 0; i < Gran; i++){ //granule post syn
	     for (int k = 0; k < MFtoGR; k++){
	      int rand4 = randGen(0, Moss);
	      outputs[rand4].push_back(Moss+i);
	      weights[rand4].push_back(initalWeight);
	     }
	     for (int k = 0; k < GOtoGR; k++){
	      int rand5 = randGen(Moss+Gran, Moss+Gran+Golg);
	      outputs[rand5].push_back(Moss+i);
	      weights[rand5].push_back(-initalWeight);
	     }
	}
	for(int i  = 0; i< Golg; i++){ ///golgi post syn
	    for (int k = 0; k < MFtoGO; k++){
	      int rand6 = randGen(0, Moss);
	      outputs[rand6].push_back(Moss+Gran+i);
	      weights[rand6].push_back(initalWeight);
	    }
	    for (int k = 0; k < GRtoGO; k++){
	      int rand7 = randGen(Moss, Moss+Gran);
	      outputs[rand7].push_back(Moss+Gran+i);
	      weights[rand7].push_back(initalWeight);
	    }
	}
	for(int i = 0; i < Bask; i++){ ///basket post syn
	    for (int k = 0; k < GRtoBK; k++){
	      int rand8 = randGen(Moss, Moss+Gran);
	      outputs[rand8].push_back(Moss+Gran+Golg+Purk+i);
	      weights[rand8].push_back(initalWeight);
	    }
	}
	for(int i = 0; i < Stel; i++){ ///stellate post syn
        for (int k = 0; k < GRtoST; k++){
              int rand9 = randGen(Moss, Moss+Gran);
              outputs[rand9].push_back(Moss+Gran+Golg+Purk+Bask+i);
              weights[rand9].push_back(initalWeight);
            }
	}
	for(int i = 0; i < Nucl; i++){ //for nuclear post syn
	    for (int k = 0; k < PRtoNC; k++){
              int rand10 = randGen(Moss+Gran+Golg, Moss+Gran+Golg+Purk);
              outputs[rand10].push_back(Moss+Gran+Golg+Purk+Bask+Stel+i);
              weights[rand10].push_back(-initalWeight);
            }
	    for (int k = 0; k < MFtoNC; k++){
              int rand11 = randGen(0, Moss);
              outputs[rand11].push_back(Moss+Gran+Golg+Purk+Bask+Stel+i);
              weights[rand11].push_back(0.001); /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            }
	}

	///now for IO
	    for(int k = 0; k < NCtoIO; k++){
	        int rand12 = randGen(Moss+Gran+Golg+Purk+Bask+Stel, Moss+Gran+Golg+Purk+Bask+Stel+Nucl);
              outputs[rand12].push_back(TotalCells-1);
              weights[rand12].push_back(-initalWeight);
	    }
	}

float conductance(int Neuron){
	float currentConductance = FullNetwork[Neuron][0];
	float conductchange = FullNetwork[Neuron][2]*(1-currentConductance) - (DecCund*currentConductance); // has to be lower than 2. ~1.2 makes the purkinjes go crazy
	FullNetwork[Neuron][2] = 0; // weight change reset
	return conductchange;
}

float Voltage(int Neuron){
	float reversalPotential = 2;
	float voltNeuron = FullNetwork[Neuron][1];
	float current = FullNetwork[Neuron][0]*(voltNeuron - reversalPotential); /// The reversal potential may cahnge with the cell type

	float voltchange = -(VoltageLeak*(voltNeuron -(-70))) - (current);///007 is hte leak conductance El is voltage at rest
	return voltchange;
}

void ChlorideFactor(){
    for(int i = 0; i < PurkinjeChlorides.size(); i++){
        if(i < NUCL){
            PurkinjeChlorides[i] -= 0.333*PurkinjeChlorides[i];
            NuclearChlorides[i] -= 0.95*NuclearChlorides[i];
        }else{
          PurkinjeChlorides[i] -= 0.333*PurkinjeChlorides[i];
        }
    }
}

float MossyVoltage(int Neuron, bool ActivatedMossy){
	float voltNeuron = FullNetwork[Neuron][1];
	float voltchange = -(VoltageLeak*(voltNeuron-(-Threshold)));
	int generatedNum = randGen(1, 4); /// not sure if it can generate one but if there is a problem with the network it is  liekly here
	if(ActivatedMossy == true){
		generatedNum = 2;
	}
	if (generatedNum == 2){
		voltchange += 30;
	}
	return voltchange;
}


void checkThreshold(int Neuron, bool WeightCheck){ // 0 if none 1 if for granule weights and 2 if for mossy fibers
	FullNetwork[Neuron][3] -= (FullNetwork[Neuron][3]-Threshold)*DecThresh; //Treshold exponenetial decay if it is to be activated
    //cout << "her";
	if(FullNetwork[Neuron][1] > FullNetwork[Neuron][3]){

	////////////////////section for putting in chlorides
		if(FullNetwork[Neuron][4] == 8){ // bc 1 cell outputs to all purkinjes
            for (int k = 0; k < outputs[Neuron].size(); k++){
                PurkinjeChlorides[(MOSS+GRAN+GOLG+PURK-1)-(outputs[Neuron][k])] += 1;
            }
            } else if(FullNetwork[Neuron][4] == 4){ //purkinje cells OOONNNNLLLLY output to nuclear cells
             for(int k = 0; k < outputs[Neuron].size(); k++){
                NuclearChlorides[((outputs[Neuron][k])-((TotalCells-1)-(IO+NUCL)))] += 1;}
		    // more expensive than the purkinje chlorides but should be fine
		}

		Outputfile[Outputfile.size()-1].push_back(Neuron);
		//cout << "FIRE" << endl;
		FullNetwork[Neuron][3] = MaxThreshold; // Threshold Increase
		FullNetwork[Neuron][1] = -80; // the difference between the current voltage subtracted to resturn to resting // 60 is resting 70 is hyperpolarized
		for(int i = 0; i < outputs[Neuron].size(); i++){
			float w = weights[Neuron][i];
			FullNetwork[(outputs[Neuron][i])][2] += w; /// would be w*#of spikes but I dont see how there could be more than one per neuron at a time

            if(FullNetwork[Neuron][4] == 2 && FullNetwork[outputs[Neuron][i]][4] == 4){
                if(PurkinjeChlorides[(MOSS+GRAN+GOLG+PURK-1)-(outputs[Neuron][i])] > 0.2){
                    weights[Neuron][i] += GranuleNegative;
                } else{
                    weights[Neuron][i] += GranulePositive;
                }
            }else if(FullNetwork[Neuron][4] == 1){ // checks if cell is MF
				if(outputs[Neuron][i] >= TotalCells-(IO+NUCL)){ //checks if the output is a nuclear cell
                    float chlorideConc = NuclearChlorides[(outputs[Neuron][i])-((TotalCells-1)-(IO+NUCL))];
                        if(chlorideConc > 1.3){
                            weights[Neuron][i] += NuclearNegative;
                        } else{
                            weights[Neuron][i] += NuclearPosititve;
                        }
				      }
				   }
				}
			}
		}

float stimuliTime = 1;
float stimuliInterval = 0.04;
float airpuffTime = 1.4;
int contINT = 0;
int testnumb;

int main(){
    cin >> testnumb;
    cin >> DecCund;
    cin >> DecThresh;
    cin >> DecChlor;
    cin >> VoltageLeak;
    cin >> NuclearW;

	initalizeNetwork(MOSS, GRAN, GOLG, PURK, BASK, STEL, NUCL, IO, NuclearW);
	InitalizeSubset(MOSS);

    string tempname = "Temp62623newPro_"+to_string(testnumb)+".txt";
    string weightname = "Weight62623newPro_"+to_string(testnumb)+".txt";
	ofstream MyFile(tempname);
	ofstream weightFile(weightname);

    int iterations = 15; //// number of times to rerun
	for(int k =0; k < iterations; k++){
	// or else it will copy everything from the previous trials

	bool go = true;
	float timenow = clock();
	float time0 = clock();
	float timezip = clock();
	int iters = 0;

	while((timenow - time0)/CLOCKS_PER_SEC < 2){
		while(go == true){
			Outputfile.push_back({});
			Outputtime.push_back((timenow - time0)/CLOCKS_PER_SEC);

			iters += 1;
			cout << iters << endl;


		timezip = clock();

		/// part 1 conductance
		for(int i = 0; i < TotalCells; i++){
			FullNetwork[i][0] += conductance(i);
			if(FullNetwork[i][0] < 0){
			FullNetwork[i][0] = 0;
			}
		}

		/// part 2 Voltage
		if(stimuliTime < (timenow - time0)/CLOCKS_PER_SEC && (airpuffTime+stimuliInterval) > ((timenow - time0)/CLOCKS_PER_SEC)){
			for(int i = 0; i < MossySubset.size(); i++){
				FullNetwork[MossySubset[i]][1] += MossyVoltage(i, true);}
		}
		if (airpuffTime < (timenow - time0)/CLOCKS_PER_SEC && (airpuffTime+stimuliInterval) > (timenow - time0)/CLOCKS_PER_SEC){
					FullNetwork[TotalCells-1][1] += 30;
	    }
		for(int i = 0; i < TotalCells; i++){
			if(i < MOSS){
				FullNetwork[i][1] += MossyVoltage(i, false);
			} else{
				FullNetwork[i][1] += Voltage(i);
			}
		}
		/// part 3 check the thresholds
		for(int i = 0; i < MOSS; i++){
			checkThreshold(i, false);
		}
		for(int i = MOSS; i < MOSS+GRAN; i++){
			checkThreshold(i, true);
		}
		for(int i = MOSS+GRAN; i < TotalCells; i++){
			checkThreshold(i, false);
		}
        ChlorideFactor();
		go = false;
	}

 timenow = clock();
if((timenow - timezip)/CLOCKS_PER_SEC > 0.015){ // the following timestep value givecs the gaussian distrubution for the mossy fiber
	go = true;
}
}
for(int i = contINT; i < Outputtime.size(); i++){
	MyFile << Outputtime[i];
	MyFile << ", ";}
	MyFile << endl;
for(int i = contINT; i < Outputtime.size(); i++){
	for(int j = 0; j < Outputfile[i].size(); j++){
	MyFile << Outputfile[i][j];
	MyFile << ", ";
	}
    MyFile << "/";
    }
    MyFile << endl;

    contINT += iters;
}
for(int i = 0; i < TotalCells; i++){
    weightFile << "[";
    for(int j = 0; j < weights[i].size(); j++){
        weightFile << weights[i][j];
        weightFile << ",";
    }
    weightFile << "]";
}

	return 0;
}

