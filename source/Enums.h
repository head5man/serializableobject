namespace serializable
{

enum class EFormat
{
    FormatCompact,
    FormatNormal,
    FormatPretty
};

/// <summary>
/// /// Additional flags
/// </summary>
enum class SerializableFlags {
	FlagNone = 0,
	/// <summary>
	/// Member is not required - no errors will be logged
	/// </summary>
	FlagOptional = 0x1,
	/// <summary>
	/// Member is a vector<T> - T defined by type
	/// </summary>
	FlagVector = 0x2,
	/// <summary>
	/// (string*) - un-(de)serialized string
	/// </summary>
	FlagRaw = 0x4
};

}