package programContent;
import java.util.Arrays;
import java.util.Stack;

/**
 * Class Content
 */
public class Content {

    /**
     * Current direction of movement of the program
     */
    public programContent.DIRECTION direction;
    /**
     * Stack of elements
     */
    public Stack<Integer> stack;
    /**
     * The variable becomes true when it encounters the first quotes
     * and becomes false when it encounters the second.
     * In this mode all characters are pushed onto the stack.
     */
    public boolean stringMode;
    /**
     * Ihe element to be pushed onto the stack
     */
    public char inStack;
    /**
     * If this variable is true then next command is skipped
     */
    public boolean bridge;
    /**
     * Befunge program text
     */
    public char[] field;
    /**
     * Maximum field size by x
     */
    public final int field_x = 80;
    /**
     * Maximum field size by y
     */
    public final int field_y = 25;

    /**
     * Constructor
     */
    public Content(){
        stack = new Stack<>();
        direction = DIRECTION.RIGHT;
        stringMode = false;
        bridge = false;
        field = new char[field_x * field_y];
        Arrays.fill(field, ' ');
    }

    /**
     * Function that safely pops the value off the stack
     * @return the value at the top of the stack or zero if stack is empty
     */
    public int pop(){
        if(!stack.empty()){
            return stack.pop();
        }
        return 0;
    }
}