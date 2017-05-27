/**
 * Pairing
 * Emily Young <emily@zavtralabs.com>
 */

#ifndef PAIRING_H
#define PAIRING_H

#include "Arduino.h"
#include "constants.h"
#include "store.h"

/**
 * Check if there's a connection on the pairing pin
 */
bool isConnected();

/**
 * Check if connection and if so, attempt pairing.
 * @return true if paired with new device.
 */
bool attemptPairing();

#endif
