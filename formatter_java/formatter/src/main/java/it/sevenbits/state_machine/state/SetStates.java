package it.sevenbits.state_machine.state;

/**
 * The type Set states.
 */
public class SetStates extends State  {

    private static final State OPEN_BRACKET = new State("OPEN_BRACKET");
    private static final State CLOSE_BRACKET = new State("CLOSE_BRACKET");
    private static final State SEMICOLON = new State("SEMICOLON");
    private static final State COMMENT = new State("COMMENT");
    private static final State TEXT = new State("TEXT");
    private static final State LETTER = new State("LETTER");
    private static final State SYMBOL = new State("SYMBOL");
    private static final State SYMBOLS = new State("SYMBOLS");

    private static final State WORD = new State("WORD");
    private static final State OPERATION = new State("OPERATION");

    private static final State START = new State("START");
    private static final State FINAL = new State("FINAL");
    private static final State DEFAULT = new State("DEFAULT");

    /**
     * Instantiates a new State.
     *
     * @param state the state
     */
    public SetStates(final String state) {
        super(state);
    }

    /**
     * Gets start.
     *
     * @return the start
     */
    public static State getSTART() {
        return START;
    }

    /**
     * Gets final.
     *
     * @return the final
     */
    public static State getFINAL() {
        return FINAL;
    }

    /**
     * Gets default.
     *
     * @return the default
     */
    public static State getDEFAULT() {
        return DEFAULT;
    }

    /**
     * Gets open bracket.
     *
     * @return the open bracket
     */
    public static State getOpenBracket() {
        return OPEN_BRACKET;
    }

    /**
     * Gets close bracket.
     *
     * @return the close bracket
     */
    public static State getCloseBracket() {
        return CLOSE_BRACKET;
    }

    /**
     * Gets semicolon.
     *
     * @return the semicolon
     */
    public static State getSEMICOLON() {
        return SEMICOLON;
    }

    /**
     * Gets comment.
     *
     * @return the comment
     */
    public static State getCOMMENT() {
        return COMMENT;
    }

    /**
     * Gets text.
     *
     * @return the text
     */
    public static State getTEXT() {
        return TEXT;
    }

    /**
     * Gets letter.
     *
     * @return the letter
     */
    public static State getLETTER() {
        return LETTER;
    }

    /**
     * Gets symbol.
     *
     * @return the symbol
     */
    public static State getSYMBOL() {
        return SYMBOL;
    }

    /**
     * Gets symbols.
     *
     * @return the symbols
     */
    public static State getSYMBOLS() {
        return SYMBOLS;
    }

    /**
     * Gets word.
     *
     * @return the word
     */
    public static State getWORD() {
        return WORD;
    }

    /**
     * Gets operation.
     *
     * @return the operation
     */
    public static State getOPERATION() {
        return OPERATION;
    }

    @Override
    public boolean equals(final Object o) {
        return super.equals(o);
    }

    @Override
    public int hashCode() {
        return super.hashCode();
    }
}


