struct core
{

    struct list_item item;
    unsigned int id;
    unsigned int sp;
    struct resource resource;
    struct list tasks;
    struct task *task;

};

void core_init(struct core *core, unsigned int id, unsigned int sp, struct task *task);
