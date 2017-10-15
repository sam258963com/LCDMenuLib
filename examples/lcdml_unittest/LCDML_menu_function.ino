/* ===================================================================== *
 *                                                                       *
 * Menu Callback Function                                                *
 *                                                                       *
 * ===================================================================== *
 *
 * EXAMPLE CODE:

// *********************************************************************
void your_function_name(void) 
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  { 
    // setup
    // is called only if it is started

    // starts a trigger event for the loop function every 100 millisecounds
    LCDML.FUNC_setLoopInterval(100); 
  }     

  if(LCDML.FUNC_loop())           // ****** LOOP ********* 
  {    
    // loop
    // is called when it is triggert
    // - with LCDML_DISP_triggerMenu( millisecounds ) 
    // - with every button status change

    // check if any button is presed (enter, up, down, left, right)
    if(LCDML.BT_chkAny()) {         
      LCDML.FUNC_goBackToMenu();
    } 
  }

  if(LCDML.FUNC_stableEnd())      // ****** STABLE END ********* 
  { 
    // loop end
    // this functions is ever called when a DISP function is quit
    // you can here reset some global vars or do nothing 
  } 
}

 
 * ===================================================================== * 
 */









// *********************************************************************
void mFunc_information(void)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {  
    // setup function
    Serial.println(F("==========================================="));
    Serial.println(F("================  FUNC ===================="));
    Serial.println(F("==========================================="));
   
    Serial.println(F("To close this"));  
    Serial.println(F("function press"));
    Serial.println(F("any button or use")); 
    Serial.println(F("back button"));
  }

  if(LCDML.FUNC_loop())           // ****** LOOP ********* 
  { 
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function   
    if(LCDML.BT_chkAny()) { // check if any button is presed (enter, up, down, left, right)
      // LCDML_goToMenu stops a running menu function and goes to the menu
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_stableEnd())      // ****** STABLE END ********* 
  { 
    // this functions is ever called when a DISP function is quit
    // you can here reset some global vars or do nothing 
  } 
}


// *********************************************************************
uint8_t g_func_timer_info = 0;  // time counter (global variable)
unsigned long g_timer_1 = 0;    // timer variable (globale variable)
void mFunc_timer_info(void)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP ********* 
  {   
    Serial.println(F("==========================================="));
    Serial.println(F("================  FUNC ===================="));
    Serial.println(F("==========================================="));
    Serial.println(F("wait 10 secounds or press back button"));     
    g_func_timer_info = 10;       // reset and set timer    
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 millisecounds

    LCDML.TIMER_msReset(g_timer_1);
    
  }


  if(LCDML.FUNC_loop())           // ****** LOOP ********* 
  { 
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function 

    // reset screensaver timer
    LCDML.SCREEN_resetTimer();
    
    // this function is called every 100 millisecounds
    
    // this method checks every 1000 millisecounds if it is called
    if(LCDML.TIMER_ms(g_timer_1, 1000)) {          
      g_func_timer_info--;                // increment the value every secound
      Serial.println(g_func_timer_info);  // print the time counter value     
    }
        
    // this function can only be ended when quit button is pressed or the time is over
    // check if the function ends normaly
    if (g_func_timer_info <= 0)
    {
      // leave this function
      LCDML.FUNC_goBackToMenu();  
    } 
  } 

  if(LCDML.FUNC_stableEnd())      // ****** STABLE END ********* 
  { 
    // this functions is ever called when a DISP function is quit
    // you can here reset some global vars or do nothing
  }  
}


// *********************************************************************
uint8_t g_button_value = 0; // button value counter (global variable)
void mFunc_p2(void)
// *********************************************************************
{ 
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {  
    // setup function
    // print lcd content
    Serial.println(F("==========================================="));
    Serial.println(F("================  FUNC ===================="));
    Serial.println(F("==========================================="));
    Serial.println(F("press a or w"));  
    Serial.println(F("count: 0 of 3"));
    // Reset Button Value
    g_button_value = 0;

    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();
    
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {    
    // the quit button works in every DISP function without any checks; it starts the loop_end function  
    if (LCDML.BT_chkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      if (LCDML.BT_chkLeft() || LCDML.BT_chkUp()) // check if button left is pressed
      {
        LCDML.BT_resetLeft(); // reset the left button
        LCDML.BT_resetUp(); // reset the left button
        g_button_value++;
        
        // update lcd content
        Serial.print(F("count: "));
        Serial.print(g_button_value); //print change content
        Serial.println(F(" of 3"));       
      }    
    }
    
    // check if button count is three
    if (g_button_value >= 3) {
      LCDML.FUNC_goBackToMenu();      // leave this function  
    }    
  }

  if(LCDML.FUNC_stableEnd())     // ****** STABLE END *********
  {
    // this functions is ever called when a DISP function is quit
    // you can here reset some global vars or do nothing
  }
}


// *********************************************************************
void mFunc_back(void)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // end function and go an layer back
    LCDML.FUNC_goBackToMenu(1);      // leave this function
  } 
}


// *********************************************************************
void mFunc_goRoot(void)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // go to root and display menu
    LCDML.MENU_goRoot();
    LCDML.DISP_menuUpdate();
  } 
}

// *********************************************************************
void mFunc_jumpToFunc(void)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // Jump to Initscreen
    if(!LCDML.OTHER_goToFunc(mFunc_test_hidden)) // menu elment id and call back function allowed
    {
      // function not found or not callable
      LCDML.MENU_goRoot();
      LCDML.DISP_menuUpdate();     
    }
  }
}




// *********************************************************************
void mFunc_screensaver()
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    Serial.println("start screensaver");
  }
}

// *********************************************************************
void mFunc_initscreen()
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    Serial.println("start initscreen");
  }

  if(LCDML.FUNC_loop())           // ****** LOOP ********* 
  {
    //
    
  }

  if(LCDML.FUNC_stableEnd())      // ****** STABLE END *********
  {
    LCDML.MENU_goRoot();
  }

  
}

// *********************************************************************
void mFunc_test_hidden()
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    Serial.println("hidden menu");
  }

  if(LCDML.FUNC_loop())           // ****** LOOP ********* 
  {
    //
    
  }

  if(LCDML.FUNC_stableEnd())      // ****** STABLE END *********
  {
  }
}


