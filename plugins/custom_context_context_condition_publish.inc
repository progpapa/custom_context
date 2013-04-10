<?php

/**
 * Create a published date for a context.
 */
class custom_context_context_condition_publish extends context_condition {

  // Omit values since it could be any time
  function condition_values() {
    return array();
  } // condition_values

  function condition_form($context) {
    $form = parent::condition_form($context);

    // Format the default value since it's saved as in the mktime() format
    if (!empty($form['#default_value'])) {
      $form['#default_value'] = array(
        'year' => date('Y', $form['#default_value'][0]),
        'month' => date('n', $form['#default_value'][0]),
        'day' => date('j', $form['#default_value'][0]),
      );
    } // if
    else {
      // Split up the current time
      $form['#default_value'] = array(
        'year' => date('Y', time()),
        'month' => date('n', time()),
        'day' => date('j', time()),
      );
    } // else

    unset($form['#options']);
    $form['#type'] = 'date';
    return $form;
  } // condition_form

  function condition_form_submit($values) {
    // Change format of date to timestamp
    return array(
      mktime(
        0, // hour
        0, // minute
        0, // second
        $values['month'],
        $values['day'],
        $values['year']
        ),
    );
  } // condition_form_submit

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
          // If the current date is after the published date then set the condition
          if ($date_time[0] <= $value) {
            $this->condition_met($context, $value);
          } // if
        } // if
      } // foreach
    } // if
  } // execute

} // custom_context_context_condition_publish
