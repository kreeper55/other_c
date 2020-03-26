package it.sevenbits.state_machine.lexer;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

/**
 * The type Set symbols.
 */
public final class SetSymbols {
    private SetSymbols() {
    }

    private static final Set<Character> ALPHABET_AND_NUMERIC = new HashSet<>(Arrays.asList(
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
            'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9')
    );


    private static final Set<Character> IGNORE_SYMBOLS = new HashSet<>(
        Arrays.asList(' ', '\n', '\t', '\b', '\r', '\f')
    );

    private static final Set<Character> ONLY_SYMBOLS = new HashSet<>(
            Arrays.asList('.', '?', '(', ')', '[', ']', ':', ',', '\'')
    );

    private static final Set<Character> DOUBLE_SYMBOLS = new HashSet<>(
            Arrays.asList('=', '&', '|', '>', '+', '-')
    );

    private static final Set<Character> SUSPICIOUS_SYMBOLS = new HashSet<>(
            Arrays.asList('+', '-', '*', '/', '%', '<', '>', '&', '|',
                    '^', '!', '=')
    );

    private static final Set<Character> MAIN_OPERATORS = new HashSet<>(
            Arrays.asList('{', '}', ';')
    );

    /**
     * Gets main operators.
     *
     * @return the main operators
     */
    public static Set<Character> getMainOperators() {
        return MAIN_OPERATORS;
    }

    /**
     * Gets double symbols.
     *
     * @return the double symbols
     */
    public static Set<Character> getDoubleSymbols() {
        return DOUBLE_SYMBOLS;
    }

    /**
     * Gets Set alphabet and numeric.
     *
     * @return the alphabet and numeric
     */
    public static Set<Character> getAlphabetAndNumeric() {
        return ALPHABET_AND_NUMERIC;
    }

    /**
     * Gets Set only symbols.
     *
     * @return the only symbols
     */
    public static Set<Character> getOnlySymbols() {
        return ONLY_SYMBOLS;
    }

    /**
     * Gets Set suspicious symbols.
     *
     * @return the suspicious symbols
     */
    public static Set<Character> getSuspiciousSymbols() {
        return SUSPICIOUS_SYMBOLS;
    }

    /**
     * Gets Set ignore symbols.
     *
     * @return the ignore symbols
     */
    public static Set<Character> getIgnoreSymbols() {
        return IGNORE_SYMBOLS;
    }
}