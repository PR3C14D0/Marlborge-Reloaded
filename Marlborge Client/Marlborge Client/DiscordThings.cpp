#pragma once

#include "DiscordThings.h"

void DiscordThings::SpamDiscordWebhook(string webhook, string msg, int quantity) {
	for (int i = 0; i < quantity; i++) {
		cpr::Post(cpr::Url{ webhook },
			cpr::Payload{ {"content", msg} });
	}
}