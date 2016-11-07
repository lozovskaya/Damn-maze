##Важное
*   ```for (std::set<std::pair<int, int> >::iterator it = corners.begin(); it != corners.end();it++) {``` - 
    Так не делай. Пиши `auto`. И пробел забыл
*   `roommed` - ужасное слово. Нет такого. Это же английский - используй `room-filled`
*   Сказал же, разные генераторы полей по внутренним функциям распихай.
```C++
switch (type) {
  case field_type::blank:
    generate_blank_field();
    break;
  case field_type::random:
    generate_random_field();
    break;
```
...

###Неважное
