/******************************************************************************\
 push_button.h by Ian Korf
\******************************************************************************/

#define DEBOUNCE 25
#define TRANSMIT_DELAY 500
#define SHORT_CLICK 500

struct pushButton {
	int pin;                  // pin # on Arduino
	int curr_button_state;    // could be off or on
	int prev_button_state;
	int click_count;          // current click count
	unsigned long click_time; // length of time in click state
	unsigned long state_init; // time state started
	unsigned long state_time; // time in state elapsed
	bool events_ready;        // button is logging events
	bool pressed;             // button is ready to report events
	int clicks;               // final clicks to report
	bool held;                // long click happend
};
typedef struct pushButton push_button;

push_button new_push_button(int pin, unsigned long t) {
	push_button bt;
	bt.pin = pin;
	bt.curr_button_state = 0;
	bt.prev_button_state = 0;
	bt.click_count = 0;
	bt.click_time = 0;
	bt.events_ready = false;
	bt.state_init = t;
	bt.state_time = 0;
	bt.clicks = 0;
	bt.held = false;
	bt.pressed = false;
	return bt;
}

push_button update_button(push_button b, unsigned long curr_time, unsigned long diff_time) {
	b.curr_button_state = digitalRead(b.pin);
	if (b.curr_button_state != b.prev_button_state) {
		b.events_ready = true;
		if (b.state_time > DEBOUNCE) {
			if (b.prev_button_state == 1) {
				if (b.state_time < SHORT_CLICK) {
					b.click_count++;
				} else {
					b.click_time = b.state_time;
				}
			}
			b.state_init = curr_time;
			b.state_time = 0;
		} else {
			//Serial.print("ignoring spike: ");
			//Serial.println(b.state_time);
		}
		b.prev_button_state = b.curr_button_state;
	} else {
		b.state_time += diff_time;
		if (b.curr_button_state == 0 && b.state_time > TRANSMIT_DELAY && b.events_ready) {
			b.events_ready = false;
			b.pressed = true;
			b.clicks = b.click_count;
			b.held = b.click_time > SHORT_CLICK ? true : false;
			b.click_count = 0;
			b.click_time = 0;
			return b;
		}
	}

	b.pressed = false;
	return b;
}
