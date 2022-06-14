# compilers-1-AlexandrDaultukaev
compilers-1-AlexandrDaultukaev created by GitHub Classroom

### ИВ-921 Даултукаев Александр.

Здесь находится описание следующих лабораторных работ:
### Lab 1 & Lab 2 & Lab 3 & Lab 4 & Lab 5 & Lab 6.
Лексер и парсер для языка C#

Для запуска необходимо:
* Склонировать этот репозиторий
* Установить Open JDK 7(или выше)
* Установить Antlr 4.9
* Установить Cmake 3
* GNU Make 4.3

Сборка грамматики:
(В корне репозитория)
```
chmod +x install_grammar.sh && ./install_grammar.sh
```

Сборка проекта:
(В корне репозитория)
```
mkdir build && cd build && cmake .. && cmake --build .
```

Опции для запуска: \
``--dump-tokens`` выводит все токены в терминал в формате: \
``Loc=<строчка, столбец> имя токена 'значение токена'`` 

``--dump-ast`` выводит AST-tree в формате XML 
Пример(examples/test.cs):
```
<program>
  <function name='main' return-type='int', return_statement=(value="Enough.", literal=1, type=STRING)/>
    <scope name='main'>
      <variable name='f' type='float'/>
      <variable name='f' type='float'/>
      <assign lhs=f, rhs=10.1, op=''/>
      <variable name='s' type='string'/>
      <assign lhs=s, rhs="Hello", op=''/>
      <variable name='c' type='char'/>
      <assign lhs=c, rhs='A', op=''/>
      <variable name='i' type='int'/>
      <assign lhs=i, rhs=10, op=''/>
      <assign lhs=f, rhs=(10, "Hello"), op='+'/>
      <variable name='d' type='float'/>
      <assign lhs=d, rhs=(10.2, 'G'), op='+'/>
      <variable name='e' type='float'/>
      <assign lhs=e, rhs=('E', 42.2), op='+'/>
      <assign lhs=f, rhs=(a, b), op='+'/>
      <call name='func', args=("Hello, World!", 3.0, 2, 1, 0.0, 0, 'R', 'U', 'N', '!')/>
    </scope>
</program>
```

``--dump-table`` выводит таблицу символов
Пример 1:
```
                  10              NUMBER  1           LVARIABLE
                  15              NUMBER  1           LVARIABLE
                   2              NUMBER  1           LVARIABLE
                   a           ASSIGN_ID  1            VARIABLE
                   b                 int  1            VARIABLE
                   c                 int  1            VARIABLE
                   d                 int  1            VARIABLE
                   i                 int  1           PVARIABLE
                   j                 int  1            VARIABLE
                main                 int  0        FUNCTION_DEF
```
Первая колонка - значение символа, указанного в коде. \
Вторая колонка - тип символа. У литератов - это NUMBER, в случае оператора присваивания: ``int b = a + 2``, ``a`` будет является ASSIGN_ID \
Третья колонка - уровень вложенности. 0 - глобальный scope. \
Четвертая колонка - описание символа. Префикс "L" говорит о том, что символ литерал, "P" - символ относится к параметру функции.

Пример 2(examples/test3.cs):
```
Scope: Global
                            sm                 int  0            VARIABLE
Scope: func
                             a                 int  1            VARIABLE
                             c                char  1      PVARIABLE_func
                             f               float  1      PVARIABLE_func
                          func                 int  0        FUNCTION_DEF
                             i                 int  1      PVARIABLE_func
                             s              string  1      PVARIABLE_func
                         smain                 int  1            VARIABLE
Scope: main
                            10              NUMBER  1           LVARIABLE
                             2              NUMBER  2           LVARIABLE
                             i                 int  1            VARIABLE
                          main               float  0        FUNCTION_DEF
                            sm                 int  1       FOROPVARIABLE
```
У каждой функции выводится свой Scope. Также существует глобальная область Global.

``-x, --to-xml``(optional) \
ключ, указывающий парсеру в какой файл записывать AST в формате XML

``--wall``(optional) \
ключ, который активирует дополнительные проверки:
  1. На неиспользуемые переменные.
  2. На пустые функции.

``--opt``(optional) \
ключ, активирующий оптимизацию AST. Из AST удаляются: \
  1. Все неиспользуемые переменные. \
  2. Пустые функции, в том числе все вызовы таких функций. \
Пример: \

```
int func(string s, int i, float f, char c) {
    int var = 42;
}

int main()
{
    string s;
    int i;
    float f;
    char c;
    func(s, c, f, i);
    return i;
}
```

Если посмотреть на AST, то оно выглядит так:
```
<program>
  <function name='func', params=(s, string; i, int; f, float; c, char), return-type='void'/>
    <scope name='func'>
      <assign lhs=(var, int), rhs=42, op=''/>
    </scope>
  <function name='main' return-type='int', return_statement=(value=i, literal=0, type=ID)/>
    <scope name='main'>
      <assign lhs=(s, string)/>
      <assign lhs=(i, int)/>
      <assign lhs=(f, float)/>
      <assign lhs=(c, char)/>
      <call name='func', args=(s, c, f, i)/>
    </scope>
</program>
```

Представленный код, хоть и создает разнообразные переменные, передаёт их в функцию, но толком ничего не делает. Результат этого кода заложен здесь:
```
return i;
```
И это является, пожалуй, самой важной частью, которую следовало бы сохранить после оптимизации.
Если к компиляции применить опцию ``--opt``, то AST будет выглядеть так:
```
<program>
  <function name='main' return-type='int', return_statement=(value=i, literal=0, type=ID)/>
    <scope name='main'>
      <assign lhs=(i, int), rhs=(1, 2), op='+'/>
    </scope>
</program>
```

``--dump-asm``(optional) \
ключ, для вывода llvm ir в терминал

``-o, --out``(optional) \
ключ, указывающий куда сохранять ll файл. Обязательно указать имя самого файла с расширением .ll

``-f, --file``(required) \
ключ, указывающий какой файл обработать до IR \
Пример:
```
Loc=<29, 48> ZERO '0'
Loc=<29, 49> RRP ')'
Loc=<29, 50> SEMICOLON ';'
Loc=<29, 52> ID 'i'
Loc=<29, 53> UNARYMATHEXP '++'
```

Запуск проекта: \
Перейти в папку `build/bin` и запустить проект с указанием любого файла, лежащего в `examples` после ключа `-f`:
```
cd build/bin && ./app -f ../../examples/nod.cs
```
Для дальнейшей компиляции промежуточного кода, следует воспользоваться командами:
Полученный .ll файл(пример, main.ll):

``llc main.ll`` 

Далее сгенерируется .s(пример, main.s)

``clang main.s -o main``

### 1. Дана грамматика. Постройте вывод заданной цепочки.
a) S : T | T '+' S | T '-' S; \
   T : F | F '*' T; \
   F : 'a' | 'b';

Цепочка: a - b * a + b

<b>Ответ:</b>

``S -> T - S`` \
``-> F - S`` \
``-> F - T + S`` \
``-> a - T + S`` \
``-> a - F * T + S`` \
``-> a - F * T + T`` \
``-> a - b * T + T`` \
``-> a - b * F + T`` \
``-> a - b * F + F`` \
``-> a - F * T + T`` \
``-> a - b * a + b``
  
b) S : 'a' S B C | 'ab' C; \
   C B : B C; \
  'b' B : 'bb'; \
  'b' C : 'bc' ; \
  'c' C : 'cc';
  
<b>Ответ:</b>

``S -> aSBC`` \
``-> aaSBCBC`` \
<code>-> aaab<b>CBCB</b>C</code> <-- Меняем все CB на BC \
<code>-> aaabB<b>CB</b>CC</code> <-- Оставшуюся CB меняем на BC \
``-> aaabBBCCC`` \
``-> aaabbBCCC`` \
``-> aaabbbCCC`` \
``-> aaabbbcCC`` <-- 'b'C : 'bc' \
``-> aaabbbccc``

### 2.Построить грамматику, порождающую язык
![Снимок экрана от 2022-03-10 18-27-09](https://user-images.githubusercontent.com/60806892/157652742-26b06d9c-80a1-4e35-b343-d8ae6d0dfc2f.png)

a)

<b>Ответ:</b>

G({a,b,c}, {S,A,B,C}, P, S) \
P: \
S-> aA \
A-> aA | B \
B-> bB | C \
C-> cC | c 

b)

<b>Ответ:</b>

G({1,0,e}, {S,A}, P, S) \
P: \
S-> 0 | 0S | 10A | e  <-- e = epsilon \
A-> 10 | 10A | e \

c)

<b>Ответ:</b>

<i>Я предполагаю, что задание требует построение палиндрома</i> \
G({0,1}, {S,A}, P, S) \
P: \
S-> 0S0 | 1S1 | 00 | 11 \

### 3. К какому типу по Хомскому относится грамматика с приведенными правилами? Аргументируйте ответ.

a)S : '0' A '1' | '01'; \
'0' A : '00' A '1'; \
A : '01'; \

<b>Ответ:</b>

<i>Контекстно-зависимая грамматика. Достичь контекстно-свободной мешает контекст во второй строчке: \
  '0' A : '00' A '1' \
  ^^ \
  вот он </i>
  
b)S : A 'b'; \
A : A 'a' | 'ba';

<b>Ответ:</b>

<i>Регулярная. В первой строчке S : A 'b', где S,A ∈ VN, 'b' ∈ VT*; \
  Во второй строке: A : A 'a' | 'ba', где A ∈ VN, 'a', 'ba' ∈ VT*;</i>

### 4.Построить КС-грамматику, эквивалентную грамматике с правилами:

S : A B | A B S; \
A B : B A; \
B A : A B; \
A : 'a'; \
B : 'b';


<b>Ответ:</b>

4)G({a,b}, {S,A,B,T}, P, S) \
P: \
S: T | TS | ASB | BSA | ASBS | BSAS \
T: BA | AB \
A: 'a' \
B: 'b'

### 5.Построить регулярную грамматику, эквивалентную грамматике с правилами:

S : A '.' A; \
A : B | B A; \
B : '0' | '1';

<b>Ответ:</b>

S: 0A | 1A | 0S | 1S \
A: .B \
B: 0B | 1B | 0 | 1

### 6.Напишите регулярное выражение для:

а)Множества идентификаторов, где идентификатор – это последовательность букв или цифр, начинающаяся с буквы или _;

b)Множества вещественных констант с плавающей точкой, состоящих из целой части, десятичной точки, дробной части, символа е или Е, целого показателя степени с необязательным знаком и необязательного суффикса типа – одной из букв f, F, l или L. Целая и дробная части состоят из последовательностей цифр. Может отсутствовать либо целая, либо дробная часть (но не обе сразу).

a)

<b>Ответ:</b>

https://regexr.com/6gkdl  <-- Все тесты переключены в Match Full

b)

<b>Ответ:</b>

https://regexr.com/6gkue  <-- Все тесты переключены в Match Full


### 7. Для регулярных выражений из предыдущего задания постройте конечные автоматы. Изобразите их в виде графа.

1.

<b>Ответ:</b>

![reg1_v2](https://user-images.githubusercontent.com/60806892/156885008-bebc0802-d519-45ad-b072-cfb7bb02c2dc.svg)

2.

<b>Ответ:</b>

![reg2](https://user-images.githubusercontent.com/60806892/156885055-95249cea-986a-44f9-8173-66b78bef1208.svg)




