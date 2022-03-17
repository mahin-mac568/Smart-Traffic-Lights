#pragma once

// Rows to skip in csv data 
const int SKIPROWS = 2;

// Light durations 
const int SYNCSTAYSGREEN = 60;
const int UNSYNCSTAYSGREEN = 30;
const int YELLOWDURATION = 10;

// Traffic types (light, medium, heavy, unsynchronized, synchronized)
const int LIGHT = 0, MEDIUM = 1, HEAVY = 2;
const int UNSYNC = 0, SYNC = 1;
