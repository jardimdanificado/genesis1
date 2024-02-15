package.terrapath = package.terrapath .. ";lib/?.t;lib/?/?.t;lib/?/?/?.t;"
String = require 'std.string'
tocstr = require 'tocstr'
-- load the main.c
local c = terralib.includec("src/main.c");
Vector2 = c.Vector2;

Room = c.Room;
Creature = c.Creature;

terra main()
    --c.main();
    var rooms:Room[c.MAP_WIDTH * c.MAP_HEIGHT];
    var creatures:Creature[c.MAX_CREATURES];
    c.strcat(creatures[0].name,tocstr.tocstr32("player"));
    creatures[0].positionLocal = [Vector2]{x = 0, y = 0};
    creatures[0].currentRoom = 0;
    creatures[0].weight = 70;
    for i=0,c.MAP_WIDTH * c.MAP_HEIGHT do
        for x=0,c.ROOM_WIDTH do
            for y=0,c.ROOM_HEIGHT do
                rooms[i].map[x][y] = 0;
                rooms[i].globalPosition = [Vector2]{x = i % c.MAP_WIDTH,y = i / c.MAP_HEIGHT};
            end
        end
    end
    for i = 0, c.MAP_WIDTH * c.MAP_HEIGHT do
        c.printf("Room: %d, %d\n", rooms[i].globalPosition.x, rooms[i].globalPosition.y);
        for j = 0, c.ROOM_WIDTH do
            for k = 0, c.ROOM_HEIGHT do
                c.printf("%d", rooms[i].map[j][k]);
            end
            c.printf("\n");
        end
    end
end

-- compile the executable
terralib.saveobj("main",{main = main}, nil, nil, false);