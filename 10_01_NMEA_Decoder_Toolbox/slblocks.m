function blkStruct = slblocks
% Specify that the product should appear in the library browser
% and be cached in its repository

Browser(1).Library = 'sl_nmea';
Browser(1).Name    = 'NMEA';
Browser(1).IsFlat  = 1;% Is this library "flat" (i.e. no subsystems)?

blkStruct.Browser = Browser;

% EOF
