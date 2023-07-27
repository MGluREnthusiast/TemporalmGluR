import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Button

#### the below principles will begin to not apply as much as we continue our tests
MOSS = 600
GRAN = 10000
GOLG = 900
PURK =20
BASK =30
STEL =30
NUCL =6
IOs =1

### edit the following below
with open('Path/Test', 'r') as f:
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
                timeSet[len(timeSet)-1].append(float(tempAdd))
                tempAdd = ""
            else:
                tempAdd += lines[k][i]
    else:
        actionSet.append([])
        tempAdd = "" ### done just to make sure there is a reset
        for i in range(len(lines[k])):
            if lines[k][i] == ",":
                tempSet.append(int(tempAdd))
                tempAdd = ""
            elif lines[k][i] == "/":
                actionSet[len(actionSet)-1].append(tempSet)
                tempSet = []
                tempAdd = ""
            else:
                tempAdd += lines[k][i]

print(len(actionSet))
MossSet = []
GranSet = []
GolgSet = []
PurkSet = []
BaskSet = []
StelSet = []
NuclSet = []
IOSet = []
for p in range(len(actionSet)):
    MossSet.append([])
    GranSet.append([])
    GolgSet.append([])
    PurkSet.append([])
    BaskSet.append([])
    StelSet.append([])
    NuclSet.append([])
    IOSet.append([])
    for i in range(len(actionSet[p])):
        MossSet[p].append(0)
        GranSet[p].append(0)
        GolgSet[p].append(0)
        PurkSet[p].append(0)
        BaskSet[p].append(0)
        StelSet[p].append(0)
        NuclSet[p].append(0)
        IOSet[p].append(0)
        if len(timeSet) != 0:
            for j in range(len(actionSet[p][i])):
                if actionSet[p][i][j] < MOSS:
                    MossSet[p][i] += 1
                elif actionSet[p][i][j] < MOSS + GRAN:
                    GranSet[p][i] += 1
                elif actionSet[p][i][j] < MOSS + GRAN + GOLG:
                    GolgSet[p][i] += 1
                elif actionSet[p][i][j] < MOSS + GRAN + GOLG + PURK:
                    PurkSet[p][i] += 1
                elif actionSet[p][i][j] < MOSS + GRAN + GOLG + PURK + BASK:
                    BaskSet[p][i] += 1
                elif actionSet[p][i][j] < MOSS + GRAN + GOLG + PURK + BASK + STEL:
                    StelSet[p][i] += 1
                elif actionSet[p][i][j] < MOSS + GRAN + GOLG + PURK + BASK + STEL + NUCL:
                    NuclSet[p][i] += 1
                elif actionSet[p][i][j] < MOSS + GRAN + GOLG + PURK + BASK + STEL + NUCL + IOs:
                    IOSet[p][i] += 1


fig, [(ax1), (ax2), (ax3), (ax4), (ax5), (ax6), (ax7), (ax8)] = plt.subplots(8, 1)
plt.subplots_adjust(left=0.1, bottom=0.3)
ax1.plot(timeSet[0], MossSet[0])
ax2.plot(timeSet[0], GranSet[0], 'tab:orange')
ax3.plot(timeSet[0], GolgSet[0], 'tab:green')
ax4.plot(timeSet[0], PurkSet[0], 'tab:red')
ax5.plot(timeSet[0], BaskSet[0], 'tab:blue')
ax6.plot(timeSet[0], StelSet[0], 'tab:pink')
ax7.plot(timeSet[0], NuclSet[0], 'tab:purple')
ax8.plot(timeSet[0], IOSet[0], 'tab:brown')

# Home button
axButn1 = plt.axes([0.1, 0.1, 0.1, 0.1])
btn1 = Button(axButn1, label="Home", color='pink', hovercolor='tomato')

iteration = 0

# To plot a graph for y = x
def plot1(event):
    for ax in fig.get_axes():
        ax.cla()
    global iteration
    iteration = 0
    fig.suptitle('Neural Activity of Cerebellar Network at {} iterations'.format(iteration))
    ax1.plot(timeSet[0], MossSet[0])
    ax2.plot(timeSet[0], GranSet[0], 'tab:orange')
    ax3.plot(timeSet[0], GolgSet[0], 'tab:green')
    ax4.plot(timeSet[0], PurkSet[0], 'tab:red')
    ax5.plot(timeSet[0], BaskSet[0], 'tab:blue')
    ax6.plot(timeSet[0], StelSet[0], 'tab:pink')
    ax7.plot(timeSet[0], NuclSet[0], 'tab:purple')
    ax8.plot(timeSet[0], IOSet[0], 'tab:brown')

    plt.draw()

btn1.on_clicked(plot1)

# Previous button
axButn2 = plt.axes([0.3, 0.1, 0.1, 0.1])
btn2 = Button(
    axButn2, label="Prev", color='pink', hovercolor='tomato')


# To plot a graph for y = x**2
def plot2(event):
    for ax in fig.get_axes():
        ax.cla()
    global iteration
    iteration -= 1
    fig.suptitle('Neural Activity of Cerebellar Network at {} iterations'.format(iteration))
    ax1.plot(timeSet[0], MossSet[0])
    ax2.plot(timeSet[0], GranSet[0])
    ax3.plot(timeSet[0], GolgSet[0], 'tab:green')
    ax4.plot(timeSet[0], PurkSet[0], 'tab:red')
    ax5.plot(timeSet[0], BaskSet[0], 'tab:blue')
    ax6.plot(timeSet[0], StelSet[0], 'tab:pink')
    ax7.plot(timeSet[0], NuclSet[0], 'tab:purple')
    ax8.plot(timeSet[0], IOSet[0], 'tab:brown')

    plt.draw()


btn2.on_clicked(plot2)

# Next button
axButn3 = plt.axes([0.5, 0.1, 0.1, 0.1])
btn3 = Button(axButn3, label="Next", color='pink', hovercolor='tomato')


# To plot a graph for y = 2x
def plot3(event):
    for ax in fig.get_axes():
        ax.cla()
    global iteration
    iteration += 1
    try:
        fig.suptitle('Neural Activity of Cerebellar Network at {} iterations'.format(iteration))
        ax1.plot(timeSet[iteration], MossSet[iteration])
        ax2.plot(timeSet[iteration], GranSet[iteration], 'tab:orange')
        ax3.plot(timeSet[iteration], GolgSet[iteration], 'tab:green')
        ax4.plot(timeSet[iteration], PurkSet[iteration], 'tab:red')
        ax5.plot(timeSet[iteration], BaskSet[iteration], 'tab:blue')
        ax6.plot(timeSet[iteration], StelSet[iteration], 'tab:pink')
        ax7.plot(timeSet[iteration], NuclSet[iteration], 'tab:purple')
        ax8.plot(timeSet[iteration], IOSet[iteration], 'tab:brown')
        plt.draw()
    except IndexError:
        plt.close(fig)

btn3.on_clicked(plot3)
plt.show()