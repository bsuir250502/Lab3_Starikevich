[Lab3_Starikevich, V5]:

Имеется очередь с информацией о больницах. Элементами очереди
являются количество всех мест в больнице, количество свободных мест и
указатель на функцию, вычисляющую (условно) расстояние от больного до
больницы. Программа ведет учет свободных мест и распределяет больных в
ближайшие больницы. Реализовать операции приема и выписки больного:
если 0 – больной выписывается, 1 – поступает в ближайшую больницу,
задается фамилия больного. По F4 – выдается состояние мест в больнице,
по F5 – завершить выполнение программы.

How to:

1. Enter the information about hospitals (#, number, coordinates (x,y), places, free places)
2. Enter the information about patients (surname, coordinates (x,y))
3. Enjoy

This project calculates patient's distance to each hospital and choose nearest one, which have free places.
If nearest hospital is full, searching will be continued. You will get error message, if each hospital have no available places.