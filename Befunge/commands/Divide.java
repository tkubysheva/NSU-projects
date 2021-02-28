package commands;

import programContent.Content;

public class Divide extends Command {

    @Override
    public void Action(Content content) {
        int a = pop(content.stack);
        int b = pop(content.stack);
        content.stack.push(b / a);
    }
}
