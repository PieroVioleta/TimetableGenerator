def strElmToIntElm(x):
    return [int(elm) for elm in x]

############
intToCourse = {}
mapeo_file = open("mapeo_numero_curso.txt")
mapeo_str = mapeo_file.read()
mapeo_file.close()
mapeo_lista = mapeo_str.split('\n')
mapeo_lista = mapeo_lista[:len(mapeo_lista) - 1]
mapeo_lista = [elm.split(',') for elm in mapeo_lista]
for elm in mapeo_lista:
    intToCourse[int(elm[0])] = elm[1]
# print(intToCourse)
###########
horarios_generados_file = open('horarios.txt')
horarios_str = horarios_generados_file.read()
horarios_generados_file.close()

# print(horarios_str)
horarios_lista_str = horarios_str.split('\n')
horarios_lista = [elm.split(' ') for elm in horarios_lista_str]
horarios_lista = [x[:len(x)-1] for x in horarios_lista]
horarios_lista = [strElmToIntElm(x) for x in horarios_lista]

horarios_lista_elm_set = [frozenset(elm) for elm in horarios_lista]

horarios_conjunto = set(horarios_lista_elm_set)

lista_final = [list(elm) for elm in horarios_conjunto]

minimo_cursos = int(input("Ingrese cantidad minima de cursos: "))

for lista_elm in lista_final:
    if(len(lista_elm) == minimo_cursos):
        print("Horario: " , end="")
        for i in range(len(lista_elm)):
            if i != len(lista_elm)-1:
                print(f"{intToCourse[lista_elm[i]]}, ", end="")
            else:
                print(f"{intToCourse[lista_elm[i]]}", end="")

        print()

final_file = open("HorariosFinal.txt", "w")
for lista_elm in lista_final:
    final_file.write("Horario: ")
    for i in range(len(lista_elm)):
        if i != len(lista_elm)-1:
            final_file.write(f"{intToCourse[lista_elm[i]]}, ")
        else:
            final_file.write(f"{intToCourse[lista_elm[i]]}")
    final_file.write("\n")

final_file.close()