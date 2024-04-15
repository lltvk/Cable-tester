#include "mbed.h"
#include <type_traits>
 #include <vector>
// константы для выводов светодиодов, кнопки ручного режима
// кнопки вперед и назад, дисплей
// пока так, дальше видно будет к каким пинам привязываться
#define LED_PIN_1 D0
#define LED_PIN_2 D1
#define LED_PIN_3 D2
#define LED_PIN_4 D3
#define MANUAL_MODE_BUTTON_PIN D4
#define FORWARD_BUTTON_PIN D5
#define BACKWARD_BUTTON_PIN D6
#define DISPLAY_PIN D7

// определение констант
const int NUM_PINS = 16;
const int NUM_CONNECTORS = 2;
const int NUM_LEDS = 4;
const int NUM_KEYBOARD_KEYS = 12;
// константа для строк
const int NUM_CONTACTS_PER_LINE = 8;


// определение перечислений
enum class Mode { MANUAL, AUTOMATIC };

// определение структуры матрицы
struct ConnectionMatrix {
    std::vector<std::vector<int>> leftToRight;
    std::vector<std::vector<int>> rightToLeft;
    };

// объявление функций
void testCableAutomatic(const ConnectionMatrix& matrix, int cableNumber);
void testCableManual();
void processKeyPress(char key);
void switchMode();
void forward();
void backward();
// функции для режима тестирования 
void initDevices();
int readCableNumber();
void displayTestButtonInstruction();
bool waitForTestButtonPress();
void checkModeChangeSignal();
//функции для ручного теста
void lightUpLEDs();
void detectActiveLines();
void displayActiveLineContacts();
void waitForManualModeButtonPress();
void navigateLines();


// объявление глобальных переменных
Mode mode = Mode::MANUAL;
char keyboardInput;
int activeLine = 0;

int main() {
    // инициализация устройств (GPIO, display, keypad, LEDs)
    initDevices();

    ConnectionMatrix matrix = {
        // слева направо
        {
            {1, 0, 0, 1, 0, 0, 1, 1}, // Pin 1
            {0, 1, 1, 0, 1, 1, 0, 0}, // Pin 2
            {1, 1, 0, 0, 1, 0, 1, 0}, // Pin 3
            {0, 0, 1, 1, 0, 1, 0, 1}  // Pin 4
        },
        // справа налево
        {
            {1, 0, 1, 0}, // Pin 1
            {0, 1, 1, 0}, // Pin 2
            {0, 1, 0, 1}, // Pin 3
            {1, 0, 1, 0}  // Pin 4
        }
    };

    while (true) {
        if (mode == Mode::MANUAL) {
            testCableManual();
        } 
        else if (mode == Mode::AUTOMATIC) {
            //тестирование в автоматическом режиме 
            //считывание номера кабеля с клавиатуры
            
            int cableNumber = readCableNumber(); // считывание номера кабеля м клавиатуры
            // индикация нажатия кнопки тестирования
            displayTestButtonInstruction();
            //ждем нажатие кнопки тестирования
            bool TestButtonPressed = waitForTestButtonPress();
            if (TestButtonPressed){
                testCableAutomatic(matrix, cableNumber); // автоматическое тестирование кабеля
            }
                        
        }
        // проверка на получение сигнала от клавиатуры
        checkModeChangeSignal();
        }

    return 0;
}

void initDevices()
{

    // инициализируем все штучки типа дисплея и лсд
}

int readCableNumber(){
    int cableNumber = 0;
    return cableNumber;

}
void displayTestButtonInstruction(){
//для дисплея

}
bool waitForTestButtonPress(){
    bool buttonPressed = false;
    // ждем когда будет нажата кнопка
    return buttonPressed;
}

// функция чек клавиатура сигнал о смене режима 
void checkModeChangeSignal() {
    // Проверяем наличие сигнала о смене режима от клавиатуры
    // Обновляем режим соответствующим образом
}

void testCableAutomatic(const ConnectionMatrix& matrix, int cableNumber) {
      // выполнение тестирования кабеля с помощью матрицы соединений
     // сравниваем кабель с матрицами  leftToRight и rightToLeft
     // если кабель соответствует какой-либо матрице, то выводится сообщение "исправен"
    //если кабель не соответствует ни одной матрице, то выводится сообщение "неисправен"
    // написала как поняла, опять же тестить надо
   
    // Извлекаем матрицы leftToRight и rightToLeft из матрицы ConnectionMatrix
    const std::vector<std::vector<int>>& leftToRight = matrix.leftToRight;
    const std::vector<std::vector<int>>& rightToLeft = matrix.rightToLeft;
     // Проверяем, совпадает ли кабель с какой-либо матрицей
    bool matched = false;
    // Проверяем матрицу leftToRight
    for (const auto& row : leftToRight) {
        if (row.size() == 0) continue; // Тут пропускаем пустые строки

        // Если номер кабеля совпадает с номером кабеля в этой строке
        if (std::find(row.begin(), row.end(), cableNumber) != row.end()) {
            printf("исправный (Left to Right)\n");
            matched=true;
            break;
        }
    }

    // Если матрица еще не совпала, проверьте матрицу RightToLeft
    if (!matched) {
        for (const auto& row : rightToLeft) {
            if (row.size() == 0) continue; // Пропускаем пустые строки

            // Если номер кабеля совпадает с номером кабеля в этой строке
            if (std::find(row.begin(), row.end(), cableNumber) != row.end()) {
                printf("Исправный (Right to Left)\n");
                matched = true;
                break;
            }
        }
    }

    // Если кабель не совпадает ни с одной матрицей
    if (!matched) {
        printf("неисправен\n");
    }
}
   
    
void testCableManual() {
    initDevices();
    // ждем нажатие кнопки
    waitForManualModeButtonPress();
    // включить светодиоды
    lightUpLEDs();

    while (true){
        //определение активных строк и отображение на экране
        detectActiveLines();
        //отображение контактов активной строки
        displayActiveLineContacts();
        //перемещение по строкам через кнопки вперед/назад
        navigateLines();
  }
}
//переопределяется void initDevices(){
    // этот блок
    // ждем нажатие кнопки ручного режима
    // зажигаем светодиоды
    // определяем активные линии и отображаем их на экране
    // используем кнопки вперед/назад для навигации по линиям
    // отображение номеров контактов активной линии

//инициализация GPIO для светодиодов, дисплея и кнопок
// устанавливаем на выход выводы светодиодов (пока так)
    DigitalOut led1(LED_PIN_1);
    DigitalOut led2(LED_PIN_2);
    DigitalOut led3(LED_PIN_3);
    DigitalOut led4(LED_PIN_4);
// устанавливаем на вход кнопки (не совсем уверена что это так делается)
    DigitalIn manualModeButton(MANUAL_MODE_BUTTON_PIN, PullUp);
    DigitalIn forwardButton(FORWARD_BUTTON_PIN, PullUp);
    DigitalIn backwardButton(BACKWARD_BUTTON_PIN, PullUp);
//инициализация дисплея
//надо написать сюда код для дисплея
void lightUpLEDs(){
    //тут код для светодиодов
}
void detectActiveLines() {
// для активной строки
}
void displayActiveLineContacts() {
// для активации дисплея
}
void waitForManualModeButtonPress() {
//код для ручного режима
}
void navigateLines() {
// навигация вперед назад
}


void processKeyPress(char key) {
    // обработка ввода с клавиатуры
    // если '*', то отменяем ввод
    // если '#', то входим в режим ввода
    // если (0-9), то обрабатываем ввод
}

void switchMode() {
    // тут будем переключаться между ручным и автоматическим режимом
}
void updateDisplay(int activeLine) {
    // обновление дисплея для отображения активной линии
    printf("перейти к линии %d/n", activeLine);
}

void forward() {
    // инкремент активной строки
    activeLine++;

    //если активная строка превышает максимум, то возвращаемся в начало
    if (activeLine >= NUM_PINS) {
        activeLine = 0;
    }

    //обновляем дисплей с новой активной строкой
    updateDisplay(activeLine);
}

void backward() {
    // декремент активной строки
    activeLine--;

    // если активная строка меньше 0, то возвращаемся к последней строке
    if (activeLine < 0) {
        activeLine = NUM_PINS - 1;
    }

    // обновляем дисплей с новой активной строкой
    updateDisplay(activeLine);
}