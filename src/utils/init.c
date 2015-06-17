#include <abi.h>
#include <fudge.h>

void main()
{

    if (!call_walk(CALL_CW, CALL_PR, 5, "home/"))
        return;

    if (!call_walk(CALL_CP, CALL_PR, 9, "bin/slang"))
        return;

    if (!call_walk(CALL_C0, CALL_PR, 17, "config/init.slang"))
        return;

    call_spawn();

}
