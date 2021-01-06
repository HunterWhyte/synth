#include "codec.h"

void send_codec_ctrl(uint8_t controlBytes[], uint8_t numBytes)
{

	HAL_I2C_Master_Transmit(&hi2c1, 0x94,  controlBytes, numBytes, HAL_MAX_DELAY);

	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);


}

uint8_t read_codec_register(uint8_t mapbyte)
{
	uint8_t receivedByte;
	HAL_I2C_Master_Transmit(&hi2c1, 0x94,  &mapbyte, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, 0x94, (uint8_t*)&receivedByte, 1, HAL_MAX_DELAY);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);

	return receivedByte;
}



void codec_ctrl_init()
{
	uint32_t delaycount;
	uint8_t CodecCommandBuffer[5];

	uint8_t regValue = 0xFF;

	HAL_GPIO_WritePin(GPIOD, 0x10, GPIO_PIN_SET);
	delaycount = 1000000;
	while (delaycount > 0)
	{
		delaycount--;
	}
	//keep codec OFF
	CodecCommandBuffer[0] = 0x0D; // Playback Ctl 1
	CodecCommandBuffer[1] = 0x01; // master mute on
	send_codec_ctrl(CodecCommandBuffer, 2);

	//begin initialization sequence (p. 32) of datasheet for CS43L22
	CodecCommandBuffer[0] = 0x00;
	CodecCommandBuffer[1] = 0x99;
	send_codec_ctrl(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x47;
	CodecCommandBuffer[1] = 0x80;
	send_codec_ctrl(CodecCommandBuffer, 2);

	regValue = read_codec_register(0x32);

	CodecCommandBuffer[0] = 0x32;
	CodecCommandBuffer[1] = regValue | 0x80;
	send_codec_ctrl(CodecCommandBuffer, 2);

	regValue = read_codec_register(0x32);

	CodecCommandBuffer[0] = 0x32;
	CodecCommandBuffer[1] = regValue & (~0x80);
	send_codec_ctrl(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x00;
	CodecCommandBuffer[1] = 0x00;
	send_codec_ctrl(CodecCommandBuffer, 2);
	//end of initialization sequence

	CodecCommandBuffer[0] = 0x04; // Power CTL 2
	CodecCommandBuffer[1] = 0xAF; // all power on
	send_codec_ctrl(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x0D; // playback control 1
	CodecCommandBuffer[1] = 0x70; // max gain mute off
	send_codec_ctrl(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x05; // clocking control
	CodecCommandBuffer[1] = 0x81; //auto detect clock
	send_codec_ctrl(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x06; // interface control 1
	CodecCommandBuffer[1] = 0x07; // I²S, up to 24-bit data, 16-bit data
	send_codec_ctrl(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x0A; //Analog ZC and SR Settings
	CodecCommandBuffer[1] = 0x00; // no zero cross or soft ramping
	send_codec_ctrl(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x27; // Limiter Control 1, Min/Max Thresholds
	CodecCommandBuffer[1] = 0x00; // limiter completely disabled
	send_codec_ctrl(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x1A | 0x80; //  PCMVolume
	CodecCommandBuffer[1] = 0x0A;
	CodecCommandBuffer[2] = 0x0A;
	send_codec_ctrl(CodecCommandBuffer, 3);

	CodecCommandBuffer[0] = 0x1F;	//  Tone Control
	CodecCommandBuffer[1] = 0x0F; // default values no EQ
	send_codec_ctrl(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x22;   // master volume
	CodecCommandBuffer[1] = 0xD8; // 0x00-full, 0x01-mute 0x01-0xFE -95db - -0db
	send_codec_ctrl(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x02; // power control
	CodecCommandBuffer[1] = 0x9E; // power up
	send_codec_ctrl(CodecCommandBuffer, 2);

	return;

}
