package commands;

import programContent.Content;

public class Not extends Command {
    @Override
    public void Action(Content content) {
        int a = pop(content.stack);
        content.stack.push(a == 0 ? 1 : 0);
    }
}
