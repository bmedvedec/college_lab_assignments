import sys


def split_and_RmDuplicates(stanja):
    stanja = ",".join(stanja).split(',')
    stanja = list(dict.fromkeys(stanja))

    return stanja


def EpsilonOkruzenjeFunc(stanja):
    temp = stanja.copy()

    while len(stanja) > 0:
        stanje = stanja.pop()
        if stanje in epsilonOkruzenja:
            for epsilonStanje in epsilonOkruzenja[stanje]:
                if epsilonStanje.find(',') != -1:
                    for eps in epsilonStanje.split(','):
                        if eps not in temp:
                            temp.append(eps)
                            stanja.append(eps)
                else:
                    if epsilonStanje not in temp:
                        temp.append(epsilonStanje)
                        stanja.append(epsilonStanje)

    stanja = temp
    stanja = split_and_RmDuplicates(stanja)
    stanja.sort()
    return stanja


def simEnka(niz):
    trenutnaStanja = []
    trenutnaStanja.append(pocStanje)
    output = []
    sljedecaStanja = []
    obavljenPrijelaz = False

    trenutnaStanja = EpsilonOkruzenjeFunc(trenutnaStanja)

    trenutnaStanja.sort()
    output.append(",".join(trenutnaStanja))

    for znak in niz:
        for stanje in trenutnaStanja:
            if (stanje, znak) in prijelazi:
                if prijelazi[(stanje, znak)] != '#':
                    if prijelazi[(stanje, znak)] not in sljedecaStanja:
                        sljedecaStanja.append(prijelazi[(stanje, znak)])
                        obavljenPrijelaz = True

        sljedecaStanja = split_and_RmDuplicates(sljedecaStanja)

        sljedecaStanja = EpsilonOkruzenjeFunc(sljedecaStanja)

        if obavljenPrijelaz == True:
            trenutnaStanja = sljedecaStanja
            trenutnaStanja.sort()
            sljedecaStanja = []
            output.append(",".join(trenutnaStanja))
        else:
            output.append("#")
            trenutnaStanja = []

        obavljenPrijelaz = False

    print("|".join(output))
    return


input = sys.stdin.read().splitlines()

ulazniNizovi = []
for niz in input[0].split('|'):
    niz = niz.split(',')
    ulazniNizovi.append(niz)

skupStanja = input[1].split(',')

skupSimbolaAbecede = input[2].split(',')

skupPrihvStanja = input[3].split(',')

pocStanje = input[4]

prijelazi = {}
for i in range(5, len(input)):
    temp = input[i].split("->")
    stanje_znak = temp[0].split(',')
    prijelazi[(stanje_znak[0], stanje_znak[1])] = temp[1]

epsilonOkruzenja = {}
for stanje in skupStanja:
    epsilonOkruzenja[stanje] = []
    for prijelaz in prijelazi:
        if prijelaz[0] == stanje and prijelaz[1] == '$':
            epsilonOkruzenja[stanje].append(prijelazi[prijelaz])

    if epsilonOkruzenja[stanje] == [] or epsilonOkruzenja[stanje] == ['#']:
        del epsilonOkruzenja[stanje]

for stanje in skupStanja:
    for znak in skupSimbolaAbecede:
        if (stanje, znak) not in prijelazi:
            prijelazi[(stanje, znak)] = '#'

for niz in ulazniNizovi:
    simEnka(niz)
