

#define M_PI 3.14159265358979323846264338327950288419716939937510
auto calc_angle(fvector LocalPos, fvector WorldPos) -> fvector {
		SPOOF_FUNC
		fvector RelativePos = WorldPos - LocalPos;
		float yaw = atan2(RelativePos.y, RelativePos.x) * 180.0f / M_PI;
		float pitch = -((acos(RelativePos.z / LocalPos.distance(WorldPos)) * 180.0f / M_PI) - 90.0f);

		return fvector(pitch, yaw, 0);
	}

auto is_shootable(fvector lur, fvector bone) -> bool {
		SPOOF_FUNC

		if (lur.x >= bone.x - 20 && lur.x <= bone.x + 20 && lur.y >= bone.y - 20 && lur.y <= bone.y + 20 && lur.z >= bone.z - 30 && lur.z <= bone.z + 30) return true;
		else return false;

	}

auto in_screen(fvector2d screen_location) -> bool {
		SPOOF_FUNC

		if (screen_location.x > 0 && screen_location.x < screen_width && screen_location.y > 0 && screen_location.y < screen_height) return true;
		else return false;

	}

inline std::wstring MBytesToWString(const char* lpcszString)
{
	SPOOF_FUNC

	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}
inline std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	SPOOF_FUNC

	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}


static float powf_(float _X, float _Y) {
	return (_mm_cvtss_f32(_mm_pow_ps(_mm_set_ss(_X), _mm_set_ss(_Y))));
}
static double GetCrossDistance(double x1, double y1, double x2, double y2) {
	return sqrtf(powf((x2 - x1), 2) + powf_((y2 - y1), 2));
}



float RandomFloat(float a, float b)
{
	SPOOF;
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
