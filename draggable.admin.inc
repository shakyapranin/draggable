<?php

/**
 * @file captivation.admin.inc
 * TODO: Enter file description here.
 */

/**
 * Form builder.
 * Draggable settings form
 */
function draggable_settings_form($form, &$form_state)
{

    //Create options of node bundles
    $node_bundles = array();
    foreach(node_type_get_types() as $node_types){
        if(!empty($node_types->type)){
            $node_bundles[$node_types->type] = $node_types->name;
        }
    }

    //Create options of product property bundles
    $product_property_bundles = field_info_bundles('product_property');
    $pp_bundles = array();
    foreach($product_property_bundles as $key=>$product_property_bundle){
        $pp_bundles[$key] = $product_property_bundle['label'];
    }

    $form['node'] = array(
        '#type' => 'hidden',
        '#title' => t('Node'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#attached' => array(
            'library' => array(
                array('system', 'drupal.collapse'),
            ),
        ),
    );
    $form['node']['node_bundles'] = array(
        '#type' => 'checkboxes',
        '#options' => $node_bundles,
        '#default_value' => variable_get('draggable_saved_node_bundles',array()),
    );


    $form['product_property'] = array(
        '#type' => 'fieldset',
        '#title' => t('Product properties to yield a ordering view.'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#attached' => array(
            'library' => array(
                array('system', 'drupal.collapse'),
            ),
        ),
    );

    $form['product_property']['productproperty_bundles'] = array(
        '#type' => 'checkboxes',
        '#options' => $pp_bundles,
        '#default_value' => variable_get('draggable_saved_product_property_bundles',array()),

    );

    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit'),
    );


    return $form;
}


/**
 * @param $form
 * @param $form_state
 * Function to save draggable settings
 */
function draggable_settings_form_submit($form, &$form_state){

    //Create an array of saved node bundles
    $saved_node_bundles = array();
    if(!empty($form_state['values']['node_bundles'])){
        foreach($form_state['values']['node_bundles'] as $nodebundles){
            if(!empty($nodebundles)){
                array_push($saved_node_bundles,$nodebundles);
            }
        }
    }

    //Create an array of saved node bundles
    $saved_product_property_bundles = array();
    if(!empty($form_state['values']['productproperty_bundles'])){
        foreach($form_state['values']['productproperty_bundles'] as $nodebundles){
            if(!empty($nodebundles)){
                array_push($saved_product_property_bundles,$nodebundles);
            }
        }
    }

    variable_set('draggable_saved_node_bundles',$saved_node_bundles);
    variable_set('draggable_saved_product_property_bundles',$saved_product_property_bundles);

}