---
name: Reporte de Bug
about: Crea un reporte de un bug
title: 'ERROR: <descripcion breve y lo que ocasiona>'
labels: bug
assignees: quserforgitp

---

> [!NOTE]  
> # 📝 Pasos para reproducir el error
> 1. **Iniciar la app** 
![Image](https://github.com/user-attachments/assets/672b441b-f999-4d0e-a085-eba5686256cb)
> 2. **Ingresar "1 " sin las comillas dobles cuando aparezca en pantalla "Seleccione una opción -> "** > [!IMPORTANT]  
![Image](https://github.com/user-attachments/assets/6501ba1a-6415-4eb3-a3fa-fbb3aaadff1d)

---------------------------------------------------------------------------------------------------------------------------------------
> [!IMPORTANT] 
> # 🎯 Resultado esperado
> El sistema **pide al usuario ingresar el nombre del alumno** que se desea registrar en la base de datos permitiendo que se introduzca el nombre

---------------------------------------------------------------------------------------------------------------------------------------

> [!CAUTION]  
> # 🐛 Resultado actual
> El sistema **se salta la parte en la que le pide al usuario el nombre del alumno** y pasa directamente a pedir la matricula
> ![Image](https://github.com/user-attachments/assets/1cc12b1e-f0b4-497e-a826-603ffa9305dd)

---------------------------------------------------------------------------------------------------------------------------------------

> [!WARNING]
> # ⚠️ Esto permite que haya alumnos registrados sin nombre en la base de datos
> ## Pasos para producir este violación de integridad de datos
> 1. **Iniciar la app**
> 2. **Ingresar "1 " sin las comillas dobles cuando aparezca en pantalla "Seleccione una opción -> "**
> 3. **Ingresar una matrícula válida "2023130a" cuando aparezca en pantalla "Introduzca una matricula para agregar a la base de datos -> "**
> ## Se registra un alumno sin nombre pero sí con matrícula, lo cual es una violación a la integridad de los datos en el sistema.
> ![Image](https://github.com/user-attachments/assets/f455dd10-c15a-442b-9794-67413f94d10c)
