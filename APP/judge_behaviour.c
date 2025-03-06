#include "judge_behaviour.h"

uint8_t JudgeUARTtemp;
uint8_t JudgeDataBuffer[JudgeBufferLength];
JudgementDataTypedef JudgeStructure;

void Judge_Calucate(uint8_t Judge[JudgeBufferLength])
{

	static uint16_t start_pos;
	static uint16_t next_start_pos;

	while (1)
	{
		memcpy(&JudgeStructure.Frame_Header, &Judge[start_pos], sizeof(Frame_Header_t));
		/*��У��ͷ֡0xA5 Ȼ��crc8У��֡ͷ ��crc16λУ������*/
		if ((JudgeStructure.Frame_Header.SOF == (uint16_t)0xA5) &&
			(1 == Verify_CRC8_Check_Sum(&Judge[start_pos], sizeof(Frame_Header_t))) &&
			(1 == Verify_CRC16_Check_Sum(&Judge[start_pos], JudgeStructure.Frame_Header.DataLength + sizeof(Frame_Header_t) + 4)))
		{
			memcpy(&JudgeStructure.cmd_id, (&Judge[start_pos] + 5), sizeof(JudgeStructure.cmd_id));
			Judge[start_pos]++;														 // ֱ����֡ͷ0xA5 ��ֹ�ظ�����
			next_start_pos = start_pos + 9 + JudgeStructure.Frame_Header.DataLength; // 9Ϊ 5λ֡ͷ 2λ���ݳ��� 2У��λ
			switch (JudgeStructure.cmd_id)
			{
			case 0x0001: // ����״̬���ݣ�3Hz ���ڷ���
			{
				memcpy(&JudgeStructure.ext_game_status, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0002: // ����������ݣ�������������
			{
				memcpy(&JudgeStructure.ext_game_result, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0003: // ����������Ѫ�����ݣ�3Hz ���ڷ���
			{
				memcpy(&JudgeStructure.ext_game_robot_HP, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0004: // ���ڷ���״̬�����ڷ������
			{
				memcpy(&JudgeStructure.ext_dart_status, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0005: // �˹�������ս���ӳ���ͷ�״̬��1Hz ���ڷ���
			{
				memcpy(&JudgeStructure.ext_ICRA_buff_debuff_zone_and_lurk_status, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0101: // �����¼����ݣ�3Hz ���ڷ���
			{
				memcpy(&JudgeStructure.ext_event_data, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0102: // ���ز���վ������ʶ���ݣ������ı����
			{
				memcpy(&JudgeStructure.ext_supply_projectile_action, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0103: // ���󲹸�վ�������ݣ��ɲ����ӷ��ͣ����� 10Hz����RM �Կ�����δ���ţ�
			{
				memcpy(&JudgeStructure.ext_supply_projectile_booking, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0104: // ���о������ݣ����淢������
			{
				memcpy(&JudgeStructure.ext_referee_warning, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0105: // ���ڷ���ڵ���ʱ��3Hz ���ڷ���
			{
				memcpy(&JudgeStructure.ext_dart_remaining_time, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0201: // ������״̬���ݣ�10Hz ���ڷ���
			{
				memcpy(&JudgeStructure.ext_game_robot_status, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0202: // ʵʱ�����������ݣ�50Hz ���ڷ���
			{
				memcpy(&JudgeStructure.ext_power_heat_data, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0203: // ������λ�����ݣ�10Hz ���ڷ���
			{
				memcpy(&JudgeStructure.ext_game_robot_pos, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0204: // �������������ݣ�1Hz ���ڷ���
			{
				memcpy(&JudgeStructure.ext_buff, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0205: // ���л���������״̬���ݣ�10Hz ���ڷ��ͣ�ֻ�п��л��������ط���
			{
				memcpy(&JudgeStructure.aerial_robot_energy, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0206: // �˺�״̬���ݣ��˺���������
			{
				memcpy(&JudgeStructure.ext_robot_hurt, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0207: // ʵʱ������ݣ��ӵ��������
			{
				memcpy(&JudgeStructure.ext_shoot_data, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0208: // �ӵ�ʣ�෢���������л������Լ��ڱ������˷��ͣ�10Hz ���ڷ���
			{
				memcpy(&JudgeStructure.ext_bullet_remaining, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x0209: // ������ RFID ״̬��3Hz ���ڷ���
			{
				memcpy(&JudgeStructure.ext_rfid_status, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;
			case 0x020A: // ���ڻ����˿ͻ���ָ���飬10Hz ���ڷ���
			{
				memcpy(&JudgeStructure.ext_dart_client_cmd, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}
			break;

			case 0x0301: // �����˼佻�����ݣ����ͷ��������ͣ����� 10Hz
			{
				memcpy(&JudgeStructure.ext_student_interactive_header_data, (&Judge[start_pos] + 7), JudgeStructure.Frame_Header.DataLength);
			}

			default:
			{
				break;
			}
			}
			start_pos = next_start_pos;
		}
		else
		{
			start_pos = 0;
			break;
		}
		if (start_pos > JudgeBufferLength)
		{
			start_pos = 0;
			break;
		}
	}
}

u8 usart3_resive;
u8 usart3_flag_start;
u8  usart3_count;

u8 USART3_RX_BUF[3];
void USART3_IRQHandler()
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		usart3_resive = USART_ReceiveData(USART3);
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		if (usart3_flag_start == 1)
		{

	}
		
	}

	
}

void USART3_SendBuff(uint8_t *buf, uint16_t len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		USART_SendData(USART3, buf[i]);	
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
		;
	}

}
