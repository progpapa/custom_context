<?php

/**
 * Expose time as a context condition.
 */
class custom_context_context_condition_timebased extends context_condition{

  /**
   * Display the start time and end time select form.
   */
  function condition_form($context) {
    $values = $this->fetch_from_context($context, 'values');

    $form['start'] = array(
      '#type' => 'fieldset',
      '#title' => t('Start time'),
      '#weight' => 0,
      '#collapsible' => FALSE,
    );

    $form['start']['hour'] = array(
      '#type' => 'select',
      '#title' => t('Hour'),
      '#options' => drupal_map_assoc(range(0,23)),
      '#default_value' => empty($values) ? '' : $values['start_hour'],
      '#required' => TRUE,
      '#weight' => 0,
    );

    $form['start']['minute'] = array(
      '#type' => 'select',
      '#title' => t('Minute'),
      '#options' => drupal_map_assoc(range(0,59)),
      '#default_value' => empty($values) ? '' : $values['start_minute'],
      '#required' => TRUE,
      '#weight' => 1,
    );

    $form['end'] = array(
      '#type' => 'fieldset',
      '#title' => t('End time'),
      '#weight' => 1,
      '#collapsible' => FALSE,
    );

    $form['end']['hour'] = array(
      '#type' => 'select',
      '#title' => t('Hour'),
      '#options' => drupal_map_assoc(range(0,23)),
      '#default_value' => empty($values) ? '' : $values['end_hour'],
      '#required' => TRUE,
      '#weight' => 0,
    );

    $form['end']['minute'] = array(
      '#type' => 'select',
      '#title' => t('Minute'),
      '#options' => drupal_map_assoc(range(0,59)),
      '#default_value' => empty($values) ? '' : $values['end_minute'],
      '#required' => TRUE,
      '#weight' => 1,
    );

    return $form;
  } // condition_form

  /**
   * Override of condition_form_submit().
   */
  function condition_form_submit($values) {
    $ret = array();
    $ret['start_hour'] = $values['start']['hour'];
    $ret['start_minute'] = $values['start']['minute'];
    $ret['end_hour'] = $values['end']['hour'];
    $ret['end_minute'] = $values['end']['minute'];
    return $ret;
  } // condition_form_submit

  function execute() {
    if ($this->condition_used()) {
      foreach ($this->get_contexts() as $context) {
        $values = $this->fetch_from_context($context, 'values');
        $start_time = mktime($values['start_hour'], $values['start_minute']);
        $end_time = mktime($values['end_hour'], $values['end_minute']);
        if ($start_time <= time() && time() < $end_time) {
          $this->condition_met($context);
        } // if
      } // foreach
    } // if
  } // execute

}  // customcontext_context_condition_timebased