function mk_nmea_mex(varargin)
%MK_NMEA_MEX Build MEX library of NMEA Toolbox
%   Detailed explanation goes here

% TODO: build debug version by varargin modifier
mex sl_nmea_parser.c nmea0183.c circularbuffer.c

end

% EOF
