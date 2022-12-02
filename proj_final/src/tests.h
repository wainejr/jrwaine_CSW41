void test_joystick()
{
    while (true) {
        int val_x = drivers::get_joystick_x();
        int val_y = drivers::get_joystick_y();
        misc::Vector<int> pos = drivers::get_joystick_pos();
        printf("x y %d %d pos (%d %d)\n", val_x, val_y, pos.x, pos.y);
    }
}

void test_button()
{
    while (true) {
        bool button = drivers::get_button_pressed();
        printf("button %d\n", (int)button);
    }
}

void test_buzzer()
{
    while (true) {
        bool button = drivers::get_button_pressed();
        if (button) {
            drivers::update_buzzer_value(1.0f);
        } else {
            drivers::update_buzzer_value(0.0f);
        }
        SysCtlDelay(10000);
    }
}

void test_display()
{
    GrContextForegroundSet(&g_context, ClrWhite);
    GrContextBackgroundSet(&g_context, ClrBlack);

    GrStringDraw(&g_context, "Exempleae", -1, 0, (g_context.psFont->ui8Height + 2) * 0, true);
    GrStringDraw(&g_context, "Tiva + BoosterPack", -1, 0, (g_context.psFont->ui8Height + 2) * 1, true);
    GrStringDraw(&g_context, "---------------------", -1, 0, (g_context.psFont->ui8Height + 2) * 2, true);
    tRectangle rect {
        40, 40, 80, 80
    };

    // GrRectFill(&sContext, &rect, (unsigned long)greenColor);
    GrContextForegroundSet(&g_context, ClrGreen);
    GrRectFill(&g_context, &rect);
    GrRectDraw(&g_context, &rect);

    while (true) { }
}

void test_menu_draw()
{
    g_game.into_menu();
    g_view_game.draw(&g_context);

    while (true) { }
}

void test_game_draw()
{
    g_game.into_playing();
    g_view_game.draw(&g_context);

    while (true) { }
}

void test_score_draw()
{
    g_game.into_showing_score();
    g_game.gameplay.score.curr_score = 128.8f;
    g_view_game.draw(&g_context);

    while (true) { }
}