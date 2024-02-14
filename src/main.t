

package.terrapath = package.terrapath .. ";lib/?.t;lib/?/?.t;lib/?/?/?.t;"
String = require 'std.string'
-- load the main.c
local c = terralib.includec("src/main.c");

terra main()
    c.main()
end

-- compile the executable
terralib.saveobj("main",{main = main}, nil, nil, false);