import sys


def minimiziraj():
    global skupStanja, skupSimbAbecede, skupPrihvStanja, pocStanje

    G = []
    G_nova = []
    skupNePrihvStanja = [
        stanje for stanje in skupStanja if stanje not in skupPrihvStanja]

    if skupPrihvStanja:
        G.append(skupPrihvStanja)
    if skupNePrihvStanja:
        G.append(skupNePrihvStanja)

    prvi_prolaz = True

    while G_nova != G:
        if prvi_prolaz:
            prvi_prolaz = False
        else:
            G = G_nova
            G_nova = []

        for grupa in G:

            if len(grupa) == 1:
                G_nova.append(grupa)
                continue

            stanje = grupa[0]
            x = [stanje]
            parovi = [
                (stanje, other_stanje)
                for other_stanje in grupa
                if stanje != other_stanje
            ]

            y = []
            for par in parovi:
                if istovjetna_stanja(par, G):
                    x.append(par[1])
                else:
                    y.append(par[1])

            G_nova.append(x)
            if y:
                G_nova.append(y)

    for grupa in G:
        if len(grupa) == 1:
            continue

        stanje = grupa[0]
        for other_stanje in grupa[1:]:
            for znak in skupSimbAbecede:
                if (other_stanje, znak) in prijelazi:
                    del prijelazi[(other_stanje, znak)]

            for prijelaz in prijelazi:
                if prijelazi[prijelaz] == other_stanje:
                    prijelazi[prijelaz] = stanje

            skupStanja.remove(other_stanje)
            if other_stanje in skupPrihvStanja:
                skupPrihvStanja.remove(other_stanje)

            if other_stanje == pocStanje:
                pocStanje = stanje

    izlaz()


def istovjetna_stanja(par, G):
    stanje1, stanje2 = par
    if stanje1 in skupStanja and stanje2 not in skupStanja or stanje1 not in skupStanja and stanje2 in skupStanja:
        return False

    for znak in skupSimbAbecede:
        prijelaz1 = prijelazi[(stanje1, znak)]
        prijelaz2 = prijelazi[(stanje2, znak)]

        if prijelaz1 == prijelaz2:
            continue

        for grupa in G:
            if prijelaz1 in grupa:
                if prijelaz2 in grupa:
                    break
                return False
            if prijelaz2 in grupa:
                return False

    return True


def ukloni_nedohvatljiva_stanja():
    global skupStanja, skupSimbAbecede, skupPrihvStanja, pocStanje

    ds = [pocStanje]

    for stanje in ds:
        for znak in skupSimbAbecede:
            if prijelazi[(stanje, znak)] not in ds:
                ds.append(prijelazi[(stanje, znak)])

    skupStanja = [stanje for stanje in skupStanja if stanje in ds]

    skupPrihvStanja = [stanje for stanje in skupPrihvStanja if stanje in ds]

    prijelazi_copy = prijelazi.copy()
    for prijelaz in prijelazi_copy:
        if prijelaz[0] not in ds:
            del prijelazi[prijelaz]


def izlaz():
    print(",".join(skupStanja))
    print(",".join(skupSimbAbecede))
    print(",".join(skupPrihvStanja))
    print(pocStanje)
    for prijelaz in prijelazi:
        print(f"{prijelaz[0]},{prijelaz[1]}->{prijelazi[prijelaz]}")


def main():
    lines = sys.stdin.read().splitlines()

    global skupStanja, skupSimbAbecede, skupPrihvStanja, pocStanje

    skupStanja = lines[0].split(',')
    skupSimbAbecede = lines[1].split(',')
    skupPrihvStanja = lines[2].split(',')
    pocStanje = lines[3]

    global prijelazi
    prijelazi = {}

    for prijelaz in lines[4:]:
        temp = prijelaz.split('->')
        stanje, znak = temp[0].split(',')
        sljed = temp[1]
        prijelazi[(stanje, znak)] = sljed

    ukloni_nedohvatljiva_stanja()

    minimiziraj()


if __name__ == '__main__':
    main()
