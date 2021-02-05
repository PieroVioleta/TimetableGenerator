def solve(cursos, lista_horarios_final):
    lista = []
    flag = True
    for elm2 in lista_horarios_final:
        for elm in cursos:
            if not elm in elm2:
                flag = False
                break
        if not flag:
            flag = True
            continue
        else:
            lista.append(elm2[len(elm2) - 1])
    return lista

file_horarios_final =  open("HorariosFinal.txt", 'r')
string_horarios_final = file_horarios_final.read()
file_horarios_final.close()

lista_horarios_final = string_horarios_final.split('\n')
lista_horarios_final = [elm[9:] for elm in lista_horarios_final]
lista_horarios_final = [elm.split(', ') for elm in lista_horarios_final]



cantidad_cursos = int(input("Ingrese cantidad de cursos a llevar(cantidad minima 3): "))
cursos = []
for i in range(cantidad_cursos):
    curso_string = ""
    nombre_curso = input("Ingrese nombre del curso: ")
    curso_string = nombre_curso
    cursos.append(curso_string)

lista_horarios_final_copy = []
for i in range(len(lista_horarios_final)):
    tmp = lista_horarios_final[i]
    tmp = [elm[:len(elm)-2] for elm in tmp]
    tmp.append(i)
    lista_horarios_final_copy.append(tmp)

filtrados = solve(cursos, lista_horarios_final_copy)
for index in filtrados:
    if len(lista_horarios_final[index]) == cantidad_cursos:
        print(f"Horarios: {lista_horarios_final[index]}")

# print(lista_horarios_final)