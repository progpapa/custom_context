<?php

/**
 * Ability to expire a context.
 */
class custom_context_context_condition_expire extends custom_context_context_condition_publish {

  /**
   * Pass in the date to check against in timestamp format.
   *
   * @param int $value The date/time to be evaluated in UNIX timestamp format
   *  defaults to time()
   */
  function execute($value = NULL) {
    if ($this->condition_used()) {
      // If nothing is passed then use now
      if (empty($value)) {
        $value = time();
      } // if

      foreach (context_enabled_contexts() as $context) {
        if ($date_time = $this->fetch_from_context($context, 'values')) {
          // If the current date is before the Expire date then set the condition
          if ($date_time[0] > $value) {
            $this->condition_met($context, $value);
          } // if
        } // if
      } // foreach
    } // if
  } // execute
} // custom_context_context_condition_expire