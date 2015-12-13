#include "mbed-drivers/mbed.h"

using mbed::util::FunctionPointer1;
using mbed::util::FunctionPointerBind;
using mbed::util::Event;

static DigitalOut led(LED1, 1);

static void blinky(int i) {
    led = i; // 1 => off, 0 => on
}

static void switch_pressed(void) {
    FunctionPointer1<void, int> ptr_to_blinky(blinky); // 関数へのポインターの生成
    FunctionPointerBind<void> bind_of_blinky_on(ptr_to_blinky.bind(0)); // 引数(0)をbind
    FunctionPointerBind<void> bind_of_blinky_off(ptr_to_blinky.bind(1)); // 引数(1)をbind
    Event e_on(bind_of_blinky_on); // LEDを光らせるイベントを生成
    Event e_off(bind_of_blinky_off); // LEDを消すイベントを生成

    // LEDを光らせるイベントをキューへ積む
    minar::Scheduler::postCallback(e_on);
    // LEDを消すイベントを1秒後に実行するようにキューへ積む
    minar::Scheduler::postCallback(e_off).delay(minar::milliseconds(1000));
}

void app_start(int, char**) {
    // SW2の入力をトリガーにしてswitch_pressedを実行
    static InterruptIn user_sw(SW2);
    user_sw.rise(switch_pressed);
}
