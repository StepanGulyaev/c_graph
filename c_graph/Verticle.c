#include "Node.h"
#include "Verticle.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Service.h"


Verticle* new_verticle()
    {
    return (Verticle*)calloc(1,sizeof(Verticle));
    }

