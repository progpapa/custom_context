<?php

/**
 * Show a custom message on the site.
 */
class custom_context_context_reaction_showmessage extends context_reaction {

  function options_form($context) {
    $values = $this->fetch_from_context($context);
    $form = array(
      'message' => array(
        '#title' => t('Enter a message'),
        '#type' => 'textarea',
        '#default_value' => isset($values['message']) ? $values['message'] : '',
      ),
    );
    return $form;
  } // options_form

  function execute() {
    foreach ($this->get_contexts() as $k => $v) {
      if (!empty($v->reactions[$this->plugin]['message'])) {
        drupal_set_message($v->reactions[$this->plugin]['message']);
      } // if
    } // foreach
  } // execute

} // custom_context_context_reaction_showmessage
