package commands;

import programContent.Content;

public class Dup extends Command {
    @Override
    public void Action(Content content) {
        int a = pop(content.stack);
        content.stack.push(a);
        content.stack.push(a);
    }
}
