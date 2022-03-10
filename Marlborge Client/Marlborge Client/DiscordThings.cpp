#pragma once

#include "DiscordThings.h"

void DiscordThings::SpamDiscordWebhook(string webhook, string msg, int quantity) {
	cpr::Post(cpr::Url{ webhook },
			  cpr::Payload{ {"content", msg}});
}