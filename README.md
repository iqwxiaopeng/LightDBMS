# СУБД LightDBMS - лучшая СУБД в мире

Разработана магистрантами кафедры Системного программирования. 

## Компиляция

Для генерации Makefile в рабочем каталоге выполните команду:

    cmake ./

Для компиляции под Linux используйте команду:
    
    make

В случае успешной компиляции в папке с проектом будет создан файл 'dbms'

## Запуск на исполнение

Для запуска СУБД из командной строки:

    # Запуск с запросом по умолчанию
    ./dbms
    
    # Запуск с произвольным запросом
    ./dbms 'запрос'
    
    # Например:
    ./dbms 'select name, price from items, users where user.id = items.userid and price > 1000;'