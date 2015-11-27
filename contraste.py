import numpy

with open("data/resultados.1448585958.csv") as f:
    with open("data/resultados.1448585958.inventoraro.csv","w") as f2:
        c = 0

        for line in f:
            if c==0:
                f2.write(line)

            else:
                elementos = line.split(',')
                elementos[-1] = elementos[-1].replace("\n","")
                Id = elementos[0]

                probabilidades =  numpy.array([float(x) for x in elementos[1:]])
                prob =([float(x) for x in elementos[1:]])

                std= numpy.std(probabilidades)

                maxi = max(prob)

                elegidos=[]


                for x in prob:
                    if  (maxi*2<1):
                        if (x>= maxi - std):
                            elegidos.append (x*2)
                        else:
                            elegidos.append (x)
                    else :
                        if (x>= maxi - std):
                            elegidos.append (x)
                        else:
                            elegidos.append (x/2)


                suma = sum(elegidos)

                f2.write(Id)

                for x in elegidos:
                    f2.write(",")
                    f2.write(str(x))

                f2.write ("\n")




            c = c+1
