package commands;

import programContent.Content;

public class Add extends Command {

    @Override
    public void Action(Content content) {
        int a = pop(content.stack);
        int b = pop(content.stack);
        content.stack.push(a + b);
    }
}
