#include <alsa/asoundlib.h>

int main()
{
	int cardNum = -1;
	int count = 0;
	int err;
	for (;;) {
		snd_ctl_t *cardHandle;
		if ((err = snd_card_next(&cardNum)) < 0) {
			fprintf(stderr, "Can't get the next card number: %s\n", snd_strerror(err));
			break;
		}

		if (cardNum < 0) break;

		{
			char str[64];
			sprintf(str, "hw:%i", cardNum);
			if ((err = snd_ctl_open(&cardHandle, str, 0)) < 0)
			{
				printf("Can't open card %i: %s\n", cardNum, snd_strerror(err));
				continue;
			}
		}
		{
			snd_ctl_card_info_t *cardInfo;
			snd_ctl_card_info_alloca(&cardInfo);
			if ((err = snd_ctl_card_info(cardHandle, cardInfo)) < 0)
			{
				printf("Can't get info for card %i: %s\n", cardNum, snd_strerror(err));
			}
			else
			{
				const char* card_name = snd_ctl_card_info_get_name(cardInfo);
				const char* card_id = snd_ctl_card_info_get_id(cardInfo);
				printf("card_name: %s, card_id: %s\n", card_name, card_id);
				count += 1;
			}
		}
		snd_ctl_close(cardHandle);
	}

	printf("Found %i cards\n", count);
	return 0;
}

