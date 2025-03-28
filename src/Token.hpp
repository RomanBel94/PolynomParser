namespace LexerParser
{
/*
    Types of used tokens
*/
enum class TokenType : unsigned char
{
    Undefined,
    Number,
    Newline,
    Eof
};

/*
    Struct for token description
*/
struct Token
{
    const int value;
    const TokenType type;

    explicit Token(const TokenType type, const short value = '\0')
        : type(type), value(value)
    {
    }
    ~Token() = default;

    inline bool operator==(TokenType rhs) const { return this->type == rhs; }

    inline bool operator!=(TokenType rhs) const { return this->type != rhs; }

    inline operator TokenType() const { return type; }
    inline operator int() const { return value; }

private:
    Token() = delete;
    Token(const Token&) = delete;
    Token(Token&&) noexcept = delete;
    const Token& operator=(const Token&) = delete;
    Token&& operator=(Token&&) noexcept = delete;
};

}; // namespace LexerParser
