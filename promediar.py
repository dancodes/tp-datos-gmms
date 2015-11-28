from __future__ import division

elementos1 = {}
elementos3 = {}

resultado = {}

with open("data/resultados.1448680177.arboles800.profundidad7.algoritmo_e.csv") as file1:
    with open("data/resultados.1448680202.arboles800.profundidad7.algoritmo_g.csv") as file2:
        with open("data/resultados.1448680202.arboles800.profundidad7.algoritmo_avg.csv","w") as file3:
            c = 0


            lines1 = file1.read().splitlines()
            lines2 = file2.read().splitlines()

            print len(lines1)
            print len(lines2)

            for c in range(0,len(lines1)):
                if c==0:
                    file3.write(lines1[0])
                else:
                    elementos = lines1[c].split(',')
                    elementos[-1] = elementos[-1].replace("\n","")
                    Id = elementos[0]
                    probabilidades = ([float(x) for x in elementos[1:]])

                    elementos1[int(Id)] = probabilidades


                    elementos2 = lines2[c].split(',')
                    elementos2[-1] = elementos2[-1].replace("\n","")
                    Id2 = elementos2[0]
                    probabilidades = ([float(x) for x in elementos2[1:]])

                    elementos3[int(Id2)] = probabilidades

            for c in range(1,len(lines1) - 1):
                file3.write(str(c))
                file3.write(",")
                resultado[c] = []
                for x in range(0,len(elementos1[c])):
                    resultado[c].append((elementos1[c][x] + elementos3[c][x]) / 2.0)
                myList = ','.join(map(str, list(resultado[c])))

                file3.write(myList)
                file3.write("\n")
