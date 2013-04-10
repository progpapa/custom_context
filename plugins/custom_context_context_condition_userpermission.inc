<?php

/**
 * Expose user permissions as a context condition.
 */
class custom_context_context_condition_userpermission extends context_condition{

  function condition_values() {
    $perms = array();
    $module_info = system_get_info('module');
    // Get list of permissions
    foreach (module_implements('permission') as $module) {
      $permissions = module_invoke($module, 'permission');
      foreach ($permissions as $name => $perm) {
        $perms[$module_info[$module]['name']][$name] = strip_tags($perm['title']);
      }
    }
    ksort($perms);
    return $perms;
  } // condition_values

  /**
   * Override of condition_form().
   */
  function condition_form($context) {
    $form = parent::condition_form($context);
    $form['#type'] = 'select';
    $form['#size'] = 15;
    $form['#multiple'] = FALSE;
    return $form;
  } // condition_form

  /**
   * Override of condition_form_submit().
   */
  function condition_form_submit($values) {
    return drupal_map_assoc(array($values));
  } // condition_form_submit

  function execute() {
    if ($this->condition_used()) {
      foreach ($this->get_contexts() as $context) {
        $perms = array_keys($this->fetch_from_context($context, 'values'));
        if (user_access($perms[0])) {
          $this->condition_met($context);
        } // if
      } // foreach
    } // if
  } // execute

}  // custom_context_context_condition_userpermission