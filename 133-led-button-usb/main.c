#include <stdio.h>
#include "hardware/gpio.h"
#include "pico/stdlib.h"

const uint LED_PIN = 25;
const uint BUTTON_PIN = 15;
const uint DEBOUNCE_MS = 20;

bool get_button_debounce(uint pin)
{
    int first = gpio_get(pin);
    sleep_ms(DEBOUNCE_MS);
    return first && gpio_get(pin);
}

void set_led(bool on)
{
    gpio_put(LED_PIN, on);
    printf("led %s\n", on ? "on" : "off");
    // выставляем уровень на выводе и сообщаем о состоянии в порт
}

bool handle_command(int command, bool led)
{
    switch(command){
        case 'e':
        led = true;
        set_led(led);
        break;
        case 'd':
        led = false;
        set_led(led);
        break;
        default:
        printf("unknown command: %c\n", command);
    }
    return led;
    // разбираем команду и возвращаем новое состояние светодиода
}

int main()
{
    // включаем стандартный ввод-вывод
    stdio_init_all();
    // инициализируем и настраиваем выводы
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);


    // объявляем переменные
    bool led = false;
    bool prev = false;
    bool current = false;


    while (1)
    {
        // читаем состояние пина кнопки с задержкой
        current = get_button_debounce(BUTTON_PIN);

        // если состояние сменилось — переключаем светодиод
        if(prev == true && current == false){
            led = !led;
            set_led(led);
        }

        // запоминаем текущее состояние пина кнопки, как предыдущее
        prev = current;

        int command = getchar_timeout_us(0);

        if (command == PICO_ERROR_TIMEOUT)
        {
            continue;
        }

        led = handle_command(command, led);
    }
}