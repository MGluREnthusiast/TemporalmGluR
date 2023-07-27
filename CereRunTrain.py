import os
import pyautogui

MOSS = 600
GRAN = 10000
GOLG = 900 ### this was 100 when i ran the sim on 4/27/23
PURK =20
BASK =30
STEL =30
NUCL = 6
IOs = 1
TotalCells = MOSS+GRAN+GOLG+PURK+BASK+STEL+NUCL+IOs

DecCund = []
DecThresh = []
DecChlor = []
VoltLeak = []
MFActiavtes = []
Threshincrease = []
NuclearWeight = []

for i in range(0, int((1.2-0.6)/0.1)):
    for j in range(0, int((0.3-0.05)/0.05)):
        for k in range(0, int((0.6-0.1)/0.1)):
                for l in range(0, int((0.1-0.02)/0.02)):
                        for p in range(0, int((0.01-0.0005)/0.0005)):
                            DecCund.append("{:.2f}".format(0.6+(0.1*i)))
                            DecThresh.append("{:.2f}".format(0.05+(0.05*j)))
                            DecChlor.append("{:.2f}".format(0.1+(0.1*k)))
                            VoltLeak.append(0.07) ### will not be testing voltage leak tonight
                            NuclearWeight.append("{:.5f}".format(0.01+(0.0005*p)))

AccuracyData = []

print(len(DecCund))
for i in range(0, len(DecCund)):
    pyautogui.moveTo(200, 700)
    pyautogui.click()
    pyautogui.write('{}'.format(i), interval=0.03)
    pyautogui.press('enter')
    pyautogui.write('{}'.format(DecCund[i]), interval=0.03)
    pyautogui.press('enter')
    pyautogui.write('{}'.format(DecThresh[i]), interval=0.03)
    pyautogui.press('enter')
    pyautogui.write('{}'.format(DecChlor[i]), interval=0.03)
    pyautogui.press('enter')
    pyautogui.write('{}'.format(VoltLeak[i]), interval=0.03)
    pyautogui.press('enter')
    pyautogui.write('{}'.format(NuclearWeight[i]), interval=0.03)
    pyautogui.press('enter')
    os.system("g++ NuevaTemporal2.cpp")
    os.system("a.exe")

    Test = "TestName_{}".format(i)
    x = "Temporal{}.txt".format(Test)
    xweight = "Weight{}.txt".format(Test)



    with open('PATH/{}'.format(x), 'r') as f:
        lines = f.readlines()
        for i in range(len(lines)):
            lines[i] = lines[i].rstrip()
            lines[i] = lines[i].replace(" ", "")
        f.close()

    timeSet = []
    actionSet = []
    tempAdd = ""
    tempSet = []
    for k in range(len(lines)):
        if k % 2 == 0:
            timeSet.append([])
            for i in range(len(lines[k])):
                if lines[k][i] == ",":
                    timeSet[len(timeSet) - 1].append(float(tempAdd))
                    tempAdd = ""
                else:
                    tempAdd += lines[k][i]
        else:
            actionSet.append([])
            tempAdd = ""  ### done just to make sure there is a reset
            for i in range(len(lines[k])):
                if lines[k][i] == ",":
                    tempSet.append(int(tempAdd))
                    tempAdd = ""
                elif lines[k][i] == "/":
                    actionSet[len(actionSet) - 1].append(tempSet)
                    tempSet = []
                    tempAdd = ""
                else:
                    tempAdd += lines[k][i]

    CloseCount = 0
    for i in range(len(timeSet)):
        for k in range(len(timeSet[i])):
            if timeSet[i][k] > 1.16: ## make sure this corresponds to the time which the error occurs
                e = 0
                for p in range(len(actionSet[i][k])):
                    if (TotalCells-1) == actionSet[i][k][p]:
                        CloseCount = CloseCount + 1
                e = e + 1
                if e > 6:
                    break
    AccuracyData.append(CloseCount)
    print(CloseCount)
    with open("Testsof626.txt", 'a') as f:
        f.write(str(CloseCount))
        f.write(" ")

print(AccuracyData)



