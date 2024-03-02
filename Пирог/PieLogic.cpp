#include "PieLogic.h"
//Сбредил для вас -- Ошлаков Данил, ИВТ-22
/*
Задача Отравленный пирог
Для игры «Отравленный пирог» используется прямоугольный пирог, разделенный на M «строк» горизонтальными разрезами и на N «столбцов» –
вертикальными. Таким образом, пирог должен быть разбит на M × N клеток, правая нижняя из которых «отравлена». Играют двое игроков, ходы
делаются по очереди. Каждый ход заключается в том, что игрок выбирает одну из еще не съеденных клеток пирога и съедает все клетки,
расположенные левее и выше выбранной (в том числе и выбранную). Проигрывает тот, кто съедает отравленную клетку. Требуется написать программу,
которая по заданной игровой позиции определяет все возможные выигрышные ходы для начинающего в этой позиции. Входные данные Данные во входном
файле расположены в следующем порядке: M, N (1 ≤ M, N ≤ 9), X1, ...,XM. Здесь Xi – число оставшихся клеток в i-м снизу горизонтальном ряду.
Все числа во входном файле разделяются пробелами и/или символами перевода строки. Выходные данные В первую строку выходного файла необходимо
вывести количество различных выигрышных ходов К, а в последующие K строк – сами выигрышные ходы. Каждый ход задается парой чисел (i, j),
где i – номер (снизу) горизонтального ряда, а j –номер (справа) вертикального ряда, которому принадлежит выбранная клетка (1 ≤ i ≤ M, 1≤ j ≤ N).
Пример входного файла
*/
//https://github.com/ivtipm/Data-structures-and-algorithms/blob/main/tasks/task_s1_dynamic_programming.md
// Процедура для выбора случайного элемента массива, который не равен нулю. Возвращает индекс
pair<int, int> randChoice(vector<vector<int>>& matrix) {
    //Индексы для случайного выбора элемента массива
    int Rcol = -1, col = matrix[0].size();
    int Rrow = -1, row = matrix.size();
    while ((Rcol == -1) || (Rrow == -1) || (matrix[Rrow][Rcol] == 0))
    {
        Rrow = rand() % row;
        Rcol = rand() % col;


    }
    return make_pair(Rrow, Rcol);
}

// Процедура для выбора случайного элемента массива, который не равен нулю. Параметры lim отвечают за то, до какой строки и столбца с конца проверять. Возвращает индекс.
pair<int, int> randChoice(vector<vector<int>>& matrix, int rowLim, int colLim) {
    //Индексы для случайного выбора элемента массива
    int Rcol = -1, col = matrix[0].size() - colLim;
    int Rrow = -1, row = matrix.size() - rowLim;
    while ((Rcol == -1) || (Rrow == -1) || (matrix[Rrow][Rcol] == 0))
    {
        Rrow = rand() % row;
        Rcol = rand() % col;


    }
    return make_pair(Rrow, Rcol);
}
// Процедура для проверки, заполнена ли матрица только 0
bool matrix0(vector<vector<int>>& matrix) {
    // Проходим по элементам матрицы
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            // Если элемент не равен 0, возвращаем false
            if (matrix[i][j] != 0) {
                return false;
            }
        }
    }

    // Если все элементы матрицы равны 0, возвращаем true
    return true;
}

// Процедура для проверки, заполнена ли матрица только 0, ограниченная снизу и справа
bool matrix0LR(vector<vector<int>>& matrix) {
    // Проходим по элементам матрицы
    for (int i = 0; i < matrix.size() - 1; i++) {
        for (int j = 0; j < matrix[i].size() - 1; j++) {
            // Если элемент не равен 0, возвращаем false
            if (matrix[i][j] != 0) {
                return false;
            }
        }
    }

    // Если все элементы матрицы равны 0, возвращаем true
    return true;
}
// Процедура для проверки, заполнена ли матрица только 0, ограниченная снизу и справа на dev
bool matrix0LR(vector<vector<int>>& matrix, int devRow, int devCol) {
    // Проходим по элементам матрицы
    for (int i = 0; i < matrix.size() - devRow; i++) {
        for (int j = 0; j < matrix[i].size() - devCol; j++) {
            // Если элемент не равен 0, возвращаем false
            if (matrix[i][j] != 0) {
                return false;
            }
        }
    }

    // Если все элементы матрицы равны 0, возвращаем true
    return true;
}

// Процедура для печати массива
void print_matrix(vector<vector<int>>& matrix) {
    // Проходим элементы матрицы и выводим их
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
// Процедура для пожирания элемента массива и всего что слева и сверху. Резалт здесь для отслеживания ходов по условию задачи
pair<int, int> devour(vector<vector<int>>& matrix, unsigned row, unsigned col) {
    // Проходим массив справа налево снизу вверх
    pair<int, int> result;
    result.first = int(row);
    result.second = int(col);
    for (int i = row; i >= 0; i--)
    {
        for (int j = col; j >= 0; j--) {
            if (matrix[i][j] == 0) {
                break;
            }
            matrix[i][j] = 0;
        }
    }
    return result;

}
// Процедура для пожирания элемента массива и всего что слева и сверху (без учета введенных координат)
void devourV(vector<vector<int>>& matrix, unsigned row, unsigned col) {
    // Проходим массив справа налево снизу вверх
    for (int i = row; i >= 0; i--)
    {
        for (int j = col; j >= 0; j--) {
            if (matrix[i][j] == 0) {
                break;
            }
            matrix[i][j] = 0;
        }
    }

}

//Число ненулевых элементов в крайнем нижней строке
int n0BR(vector<vector<int>>& matrix) {
    int count = 0;

    // Проходим по крайней нижней строке матрицы
    for (int j = 0; j < matrix[0].size(); j++) {
        // Если элемент не равен 0, увеличиваем счетчик
        if (matrix[matrix.size() - 1][j] != 0) {
            count++;
        }
    }

    return count;
}
//Число ненулевых элементов в крайнем справа столбце
int n0RC(vector<vector<int>>& matrix) {
    int count = 0;

    // Проходим по крайнему правому столбцу матрицы
    for (int i = 0; i < matrix.size(); i++) {
        // Если элемент не равен 0, увеличиваем счетчик
        if (matrix[i][matrix[0].size() - 1] != 0) {
            count++;
        }
    }

    return count;
}
int getRand(int n) {
    // Генерируем случайное число в диапазоне от 0 до RAND_MAX
    int random_number = rand();

    // Делим случайное число на RAND_MAX, чтобы получить число в диапазоне от 0 до 1
    double random_fraction = (double)random_number / RAND_MAX;

    // Умножаем случайную дробь на n, чтобы получить случайное число в диапазоне от 0 до n
    random_number = (int)(random_fraction * n);

    return random_number;
}

//Анализ ситуации
pair<int, int> termine(vector<vector<int>>& matrix)
{
    int n0BRV = n0BR(matrix);
    int n0RCV = n0RC(matrix);
    pair<int, int> result;
    //Треугольник смерти -- Треугольник стороны которого равны. Треугольник, из которого нельзя сбежать -- со сторонами 1
    //01
    //12
/* Неразрешимая ситуация.Из нее нет выхода, если он появился на вашем ходу(то есть вам выбирать).Вы выбираете 1, противник забирает 1, вам
 остается забрать только 2 (яд). При этом он работает для любых значений, если он равносторонний и у вас другой
 нет точки для выбора

 */
 //Поэтому проверяем на наличие спасения
 //11
 //12
     //Если нас загнали в треугольник смерти, длина сторон которого не равна 1, то мы можем выбраться
    if ((n0BRV == n0RCV) && matrix0LR(matrix))
    {
        if ((n0BRV == 2) && (n0RCV == 2))
        {
            //Если есть еще один элемент для пожирания
            if (matrix[matrix.size() - 2][matrix[0].size() - 2] != 0)
            {
                return devour(matrix, matrix.size() - 2, matrix[0].size() - 2);
            }
            //Иначе глотаем что осталось и умираем
            else
            {
                cout << "Dead" << endl;
                return devour(matrix, matrix.size() - 1, matrix[0].size() - 1);

            }
        }
        else
        {
            //Делаем вид, что случайно выбираем, какую из сторон обгрызать
            if (rand() % 2 == 0)
            {
                return devour(matrix, matrix.size() - 1, matrix[0].size() - 3);
            }
            else
            {
                return devour(matrix, matrix.size() - 3, matrix[0].size() - 1);
            }
        }



    }
    //Попытка добиться треугольника смерти как результат своего хода. Принудительно уравнивает стороны
    if (matrix0LR(matrix, 2, 2) || ((n0BRV != n0RCV) && ((n0RCV != matrix.size() || n0BRV != matrix[0].size()))))
    {
        //Если есть для противника способ сбежать из треугольника смерти, то треугольник не делаем, а сначала убиваем шансы на побег
        if (matrix[matrix.size() - 2][matrix[0].size() - 2] == 0)
        {
            //Если элементов в строке больше, чем в столбце
            if (n0BRV > n0RCV)
            {
                return devour(matrix, matrix.size() - 1, matrix[0].size() - 1 - n0RCV);
            }
            //Если элементов в столбце больше, чем в строке
            else
            {
                return devour(matrix, matrix.size() - 1 - n0BRV, matrix[0].size() - 1);
            }
        }
        else
        {
            return devour(matrix, matrix.size() - 2, matrix[0].size() - 2);

        }
    }
    //Если ситуация:
    /*
    01
    02
    или
    00
    12
    */
    if ((n0BRV == 1) || (n0RCV == 1))
    {
        //Если элемент в строке последней == 1
        if (matrix[matrix.size() - 1][matrix[0].size() - 2] != 0)
        {
            return devour(matrix, matrix.size() - 1, matrix[0].size() - 2);
        }
        //Если элемент в последнем столбце == 1
        else
        {
            return devour(matrix, matrix.size() - 2, matrix[0].size() - 1);
        }
    }

    //Немного разнообразия для алгоритма (на первых этапах игры). Активируется только в том случае, если ни один из 
    //вышеперчисленных триггеров не сработал
    if (rand() % 4 == 0)
    {
        if (rand() % 2 == 0)
        {
            return devour(matrix, getRand(matrix.size() - 2), matrix[0].size() - 1);
        }
        else
        {
            return devour(matrix, matrix.size() - 1, getRand(matrix[0].size() - 2));
        }
    }
    else
    {
        result = randChoice(matrix, 1, 1);
    }
    return devour(matrix, result.first, result.second);

}
//Запуск игры (умный против умного)
void executeSmVsSm(vector<vector<int>>& matrix)
{
    cout << "Матрица стартовая " << endl;
    print_matrix(matrix);
    pair<int, int> VIndex;
    //Проверка на правильность выбранного элемента
    bool pass = false;
    while (matrix[matrix.size() - 1][matrix[0].size() - 1])
    {
        cout << "Результат хода У1:" << endl;
        termine(matrix);
        print_matrix(matrix);
        cout << "Поглощено" << endl;
        cout << VIndex.first << " " << VIndex.second << endl;
        if (matrix[matrix.size() - 1][matrix[0].size() - 1] == 0)
        {
            cout << "Проиграл У1" << endl;
            break;
        }
        cout << "Результат хода У2" << endl;
        VIndex = termine(matrix);
        //devour(matrix, VIndex.first, VIndex.second);
        print_matrix(matrix);
        cout << "Поглощено" << endl;
        cout << VIndex.first << " " << VIndex.second << endl;
        if (matrix[matrix.size() - 1][matrix[0].size() - 1] == 0)
        {
            cout << "Проиграл У2" << endl;
            break;
        }
    }
}
//Запуск игры (умный против не очень умного)
void executeSmVsSt(vector<vector<int>>& matrix)
{
    cout << "Матрица стартовая " << endl;
    print_matrix(matrix);
    pair<int, int> VIndex;
    //Проверка на правильность выбранного элемента
    bool pass = false;
    while (matrix[matrix.size() - 1][matrix[0].size() - 1])
    {
        cout << "Результат хода У1:" << endl;
        VIndex = termine(matrix);
        print_matrix(matrix);
        cout << "Поглощено" << endl;
        cout << VIndex.first << " " << VIndex.second << endl;
        if (matrix[matrix.size() - 1][matrix[0].size() - 1] == 0)
        {
            cout << "Проиграл У1" << endl;
            break;
        }

        cout << "Результат хода Г1" << endl;
        VIndex = randChoice(matrix);
        devour(matrix, VIndex.first, VIndex.second);
        print_matrix(matrix);
        cout << "Поглощено" << endl;
        cout << VIndex.first << " " << VIndex.second << endl;
        if (matrix[matrix.size() - 1][matrix[0].size() - 1] == 0)
        {
            cout << "Проиграл Г1" << endl;
            break;
        }
    }
}
//Запуск игры (умный против человека)
void executeSmVsH(vector<vector<int>>& matrix)
{
    cout << "Матрица стартовая " << endl;
    print_matrix(matrix);
    //Сохранение введенных значений
    pair<int, int> VIndex;
    bool pass = false;
    //Цикл игры
    //Пара чисел для выбора пожираемого элемента
    while (matrix[matrix.size() - 1][matrix[0].size() - 1])
    {
        //Очистка проверки правильности выбранного значения (координаты не должны указывать на 0)
        pass = false;
        //Ход программы
        cout << "Результат умного хода:" << endl;
        VIndex = termine(matrix);
        cout << "Поглощено" << endl;

        cout << VIndex.first << " " << VIndex.second << endl;
        print_matrix(matrix);
        if (matrix[matrix.size() - 1][matrix[0].size() - 1] == 0)
        {
            cout << "Проиграл Умный" << endl;
            break;
        }
        //Ход игрока

        while (pass == false)
        {
            cout << "Введите координаты того, что нужно сожрать" << endl;
            cin >> VIndex.first;
            cin >> VIndex.second;
            if (matrix[VIndex.first][VIndex.second] != 0)
                pass = true;
        }
        devour(matrix, VIndex.first, VIndex.second);



        cout << "Результат ТВОЕГО ХОДА" << endl;
        print_matrix(matrix);
        cout << "Поглощено" << endl;

        cout << VIndex.first << " " << VIndex.second << endl;
        if (matrix[matrix.size() - 1][matrix[0].size() - 1] == 0)
        {
            cout << "Проиграл ТЫ" << endl;
            break;
        }
    }



}

// Процедура для создания и заполнения матрицы целых чисел row × col элементов
vector<vector<int>> create_matrix(int row, int col) {
    // Создаем двумерный вектор целых чисел
    vector<vector<int>> matrix(row, vector<int>(col));

    // Заполняем матрицу при помощи cin
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> matrix[i][j];
        }
    }

    // Возвращаем матрицу
    return matrix;
}

//Тестирование функций
void test() {
    {
        // Тестовые матрицы
        vector<vector<int>> matrix1 = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
        vector<vector<int>> matrix2 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
        vector<vector<int>> matrix3 = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

        // Тестирование n0BR
        assert(n0BR(matrix1) == 1);
        assert(n0BR(matrix2) == 3);
        assert(n0BR(matrix3) == 0);

        // Тестирование n0RC
        assert(n0RC(matrix1) == 1);
        assert(n0RC(matrix2) == 3);
        assert(n0RC(matrix3) == 0);
    }
    {
        // Тестовые матрицы
        vector<vector<int>> matrix1 = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
        vector<vector<int>> matrix2 = { {0, 0, 1}, {0, 0, 1}, {1, 1, 1} };
        vector<vector<int>> matrix3 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

        // Тестирование matrix0
        assert(matrix0(matrix2) == false);
        assert(matrix0(matrix1) == true);
        assert(matrix0(matrix3) == false);

        // Тестирование matrix0LR
        assert(matrix0LR(matrix2, 1, 1) == true);
        assert(matrix0LR(matrix1, 1, 1) == true);
        assert(matrix0LR(matrix3, 1, 1) == false);

        // Тестирование devourV
        vector<vector<int>> Tmatrix1 = { {0, 0, 0}, { 0, 0, 0 }, { 0, 0, 0 } };
        vector<vector<int>> Tmatrix3 = { {0, 0, 3}, {0, 0, 6}, {7, 8, 9} };
        devourV(matrix3, 1, 1);
        assert(matrix3 == Tmatrix3);
        devourV(matrix1, 1, 1);
        assert(matrix1 == Tmatrix1);



    }

}

