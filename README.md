# Детерминирование конечного автомата
#### Реализация алгоритма детерминирования конечного автомата и эмулирование работы КДА.
-----------------------

### Содержание:
* [Теоретическая часть](#Теоретическая-часть)
* [Пояснение к програмной реализации](#Пояснение-к-програмной-реализации)
* [Иструкция по пользованию программой](#Иструкция-по-пользованию-программой)


### Теоретическая часть

Конечный автомат A это кортеж вида
<font face="Symbol"><br />A = (V, Q, q<sub>0</sub>, F, &#x3B4)<br /></font>
`(V, Q, q0, F, t)`, 
где `V = {a1, a2, ..., an}` - множество входных символов (входной алфавит), `Q = {q0, q1, ..., qs}` - множество состояний автомата (а в представлении автомата в виде графа, размеченным над V, мэто множество вершин этого графа), `q0` - начальное состояние автомата (q0 in Q /перевести в LATex/), `F` - множество выходных состояний автомата (F - подмножество Q), `t` - функция переходов, то есть `t: QxV -> 2^Q`. При этом, если множество состояний `Q` конечно, то и автомат называют конечным.
Автомат называется детерминированным, если для лбого входного символа `ai` и любого состояния `qj` функция `t(ai, qj)` 'ведет' ровно в одну вершину, то есть `|t(ai, qj)| = 1`. Это свойство автомата (детерминированность) дает возможность реализовать его алгоритмом однозначно.

-------
Входной алфавит всегда дополняется фиктивным символом `a0` (чаще обозначают lambda - исправлю), что имеет смысл пустого символа. По такому символу тоже может быть переход, но это сразу делает автомат недетерминированным, так как в вершине, откуда есть переход и по `a0` и по символу  `ai` из V, если следующий символ именно `ai`, то поведение автомата неопределено. Такие переходы будем называть лямбда-переходами.

------
А теперь к сути проблемы: алгоритм построения конечного детерминированного автомата (далее КДА) по недетерминированному конечному автомату (НДА). Прежде всего, необходимо доказать, что для любого НДА это возможно.
Делать я этого, конечно, не буду, так как сам алгоритм детерминизации и будет являться доказательством теоремы о детерминизации.

Алгоритм детерминизации НДА состоит из двух преобразований:
```НДА -> (удаление лямбда-переходов) -> квазидетерминированный конечный автомат -> (детерминизация ККА)```
Из контекста *очевидно*, что ККА есть КНА без лямбда-переходов.

#### 1. Удаление лябда-переходов
Алгоритм удаления лямбда-переходов строится на нескольких правилах:
1) Все состояния, кроме начального, в которые можно перейти только по пустым переходам (синоним лямбда-перехода), удаляются, таким образом переопределяется множество состояний `Q` в новое множество `Q'`. Очевидно, что `Q'` принадлежит `Q`. При этом полагаем, что начальное состояние остается прежним. Результат этой операции есть автомат, назовем его `M'`. Это правило выполняется за `О(|Q|)` для каждой вершины (необходимо просмотреть, какие вешины ведут в рассматриваемую не по лямбда-переходу, то есть просмотреть все |Q| - 1 вершину и их переходы).
2) Множество дуг конечного автомата `M'` и их меток (тем самым и функция переходов `t'`) определяется так:
для любых двух состояний `p` и `r`, принадлежащих `Q'`, `r in t(p, ai)` тогда и только тогда, когда `ai in V`, а в графе `M` имеет место одно из двух: либо существует дуга из `p` в `r` с меткой `ai`, либо существует состояние `g`, такое, что из `p` в `g` сущетвует лямбда-переход и из `g` в `r` существует переход по `ai`. (требуются рисунки, будут позже). Такая проверка для каждой вершины происходит за `О(|Q|)`, аналогично предыдущему случаю.
3) Если из вершины `w` имеется лямбда-переход в вершину `f`, где `f in F`, то есть выходную вершину, и для любого 

#### 2. Детерминизация квазидетерминированного конечного автомата
Теперь, когда у нас есть квазидетерминированный автомат, можно проводить непосредственно детерминизацию.
Представим ККА в виде следующей таблицы:

| Состояние из Q\ символ из V | a1            | a2        |              | ai           |                 | an               |
|-----------------------------|---------------|-----------|--------------|--------------|-----------------|------------------|
| q1                          | {q2, q5, q42} | {q1, q2}  |              | {q3, q5, q7} |                 | {}               |
| q2                          | {}            | {qs}      |              |              |                 |                  |
|                             |               |           |              |              |                 |                  |
| qj                          |               |           |              |              |                 |                  |
|                             |               |           |              |              |                 |                  |
|                             |               |           |              |              |                 |                  |
| qs                          | {q1}          | {q2, q15} |              |              |                 | {q1, q2, q3, q5} |

Таблица построена следующим образом: по вертикали - состояния ККА, по горизонтали - буквы входного алфавита. На пересечении значение новой функции переходов, результат которой в общем случе есть пожмножество множества состояний. Необходимо построить по этой матрице новую матрицу, элементами которой будет ровно один элемент множества состояний (это эквивалентно поставленной задаче) и назвать все это новым автоматом и вообще ответом. Разрешается добавлять состояния, но не расширять входной алфавит.

Для описания алгоритма введем понятие детерминированной вершины. Детерминированная вершина (ДВ) - это такая вершина, из которой по любому входному символу существует переход в ровно одно состояние. Таким образом КДА - множество детерминированных вершин с общим входным алфавитом и множеством состояний (я уточню эквивалентность определений на ФН позже, так как термин ДВ был придуман не так давно, в начале ноября 2017).

Новый автомат определим как пятерку `(V, S, s0, F, t)`, где `S = 2^Q`. То есть мы имеем полное право в новом автомате назвать вершину `{q1, q3, a5}`, и после детерминирования каждой вершины дать всем вершинам новые названия, номера, id.

Алгоритм детерминизации ККА по таблице переходов:
1) `s0 <- {q0}`; `K <- [{q0}]` - множество вершин для детерминизации (hash-table). `D` <- [] - множество детерминированных вершин, тоже хеш-таблица. Примечание: считаем, что `q0` - стартовая вершина. 
2) Пока `K` не пусто, `s <- K.достать_любой()`, детерминировать `s`, добавить `s` в множество детерминированных вершин `D`.
3) Переименовывание вершин нового автомата (отображение в другое множество, по сути и не нужно.)

Алгоритм детерминирования вершины `s = {qi1, qi2, ..., qip}`:
1) Для каждого входного символа `ai`: `si <- {} \/ t(qi1,ai) \/ t(qi2,ai) \/ ... \/ t(qip,ai)`, добавить в `K` вершину `si`, если ее нет в `D`. Эта операция требует `p` объединений `p` подмножеств размер которых максимум `|Q|`. Тогда сложность такой операции `T = p * |Q|`. и таких операций ровно `|V|`. 
Тогда `T({qi1, qi2, ..., qip}) = p * |Q| * |V|`.
2) Определить в новую таблицу элемент `t(s, ai) = si`; `T = const`.

Теперь вернемся к основному алгоритму (описанному выше). Первая операция выполняется строго один раз, причем за константу, так что на сложность оня уже никак не может влиять.
Вторая операция в худшем случае может выполнится `2^|Q|` раз, и учитывая, что сложность детерминирования вершины, которая имеет смысл множества из `p <= |Q|` состояний, равна `T({qi1, qi2, ..., qip}) = p * |Q| * |V|`, можно сказать, что сложность алгоритма: `T(|Q|,|V|) = |Q|^2 * |V| * 2^|Q|`. Это верно, но грубо.
Рассмотрим худший вариант, когда все `2^|Q|` новых вершин придется детерминировать. Из них только 1 вершина имеет максимальную мощность, новно `|Q|` имеет мощность `n-1`, в общем случае, ровно `С(|Q|, p)` имеет можность `p`. Тогда `T(|Q|,|V|) = (1 * |Q| * |V|) * С(|Q|, 1) + (2 * |Q| * |V|) * С(|Q|, 2) + ... (i * |Q| * |V|) * С(|Q|, i) + .... + (|Q| * |Q| * |V|) * С(|Q|, |Q|) = |Q| * |V| * sum(C(|Q|,k)*k, 0 <= k <= |Q|) = |Q|^2 * |V| * 2^(|Q|-1)`.
Это лучше, но асимптотика не уменьшилась. Таким образом, `T(|Q|,|V|) = O( |Q|^2 * |V| * 2^|Q| )`.


















### Пояснение к програмной реализации
### Иструкция по пользованию программой





