#include "FIRE_key_event.h"
void deal_key_event()
{
    KEY_MSG_t keymsg;

    while(get_key_msg(& keymsg))     //��ð����ͽ��д���
    {
        if(keymsg.status == KEY_DOWN)
        {
            switch(keymsg.key)
            {
            case KEY_U:
              //��Ӱ�������
                break;

             case KEY_D:
                  //��Ӱ�������
                break;

            case KEY_L:
             //��Ӱ�������
                break;

            case KEY_R:
               //��Ӱ������� 
                break;

            case KEY_A:
                 //��Ӱ�������
                break;



            default:
                break;
            }
        }
        else if(keymsg.status == KEY_HOLD)
        {
            switch(keymsg.key)
            {
            case KEY_U:
              //��Ӱ�����������
                break;

            case KEY_D:
               //��Ӱ�����������
                break;

            case KEY_L:
               //��Ӱ�����������
                break;

            case KEY_R:
               //��Ӱ�����������
                break;

            case KEY_A:               
                //��Ӱ�����������
                break;

            default:            //����Ҫ���� cancel
                break;
            }
        }
        else
        {
            
        }
    }
}





