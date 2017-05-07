#ifndef BUZZER_H
#define BUZZER_H

#include "circularqueue.h"
#include "config.h"
#include "fastio.h"
#include "macros.h"
#include "temperature.h"

#define TONE_QUEUE_LENGTH 4

/**
 * @brief Tone structure
 * @details Simple abstraction of a tone based on a duration and a frequency.
 */
struct tone_t {
  uint16_t duration;
  uint16_t frequency;
};

/**
 * @brief Buzzer class
 */
class Buzzer {
private:
  struct state_t {
    tone_t tone;
    uint32_t endtime;
  } state;

protected:
  CircularQueue<tone_t, TONE_QUEUE_LENGTH> buffer;

  /**
   * @brief Inverts the sate of a digital PIN
   * @details This will invert the current state of an digital IO pin.
   */
  void invert() { TOGGLE(BEEPER_PIN); }

  /**
   * @brief Turn off a digital PIN
   * @details Alias of digitalWrite(PIN, LOW) using FastIO
   */
  void off() { WRITE(BEEPER_PIN, LOW); }

  /**
   * @brief Turn on a digital PIN
   * @details Alias of digitalWrite(PIN, HIGH) using FastIO
   */
  void on() { WRITE(BEEPER_PIN, HIGH); }

  /**
   * @brief Resets the state of the class
   * @details Brings the class state to a known one.
   */
  void reset() {
    this->off();
    this->state.endtime = 0;
  }

public:
  /**
   * @brief Class constructor
   */
  Buzzer() {
    SET_OUTPUT(BEEPER_PIN);
    this->reset();
  }

  /**
   * @brief Add a tone to the queue
   * @details Adds a tone_t structure to the ring buffer, will block IO if the
   *          queue is full waiting for one slot to get available.
   *
   * @param duration Duration of the tone in milliseconds
   * @param frequency Frequency of the tone in hertz
   */
  void tone(uint16_t const &duration, uint16_t const &frequency = 0) {
    while (buffer.isFull()) {
      this->tick();
     tempManager.manageTemp();
    }
    this->buffer.enqueue((tone_t){duration, frequency});
  }

  /**
   * @brief Loop function
   * @details This function should be called at loop, it will take care of
   *          playing the tones in the queue.
   */
  virtual void tick() {
    const millis_t now = millis();

    if (!this->state.endtime) {
      if (this->buffer.isEmpty())
        return;

      this->state.tone = this->buffer.dequeue();
      this->state.endtime = now + this->state.tone.duration;

      if (this->state.tone.frequency > 0) {
        this->on();
      }
    } else if (ELAPSED(now, this->state.endtime))
      this->reset();
  }
};

extern Buzzer buzzer;

#endif
