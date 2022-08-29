#include "webserv.hpp"

//associate extensions to content-types
const map<string, string> init_typemap(void) {
	try {
		PRINTCOLOR(BLUE, "Initializing extension to content-type static map.")
		map<string, string> typemap;

		//text
		typemap[".html"] = "text/html";
		typemap[".htm"] = "text/html";
		typemap[".shtml"] = "text/html";
		typemap[".css"] = "text/css";
		typemap[".txt"] = "text/plain";
		typemap[".xml"] = "text/xml";
		typemap[".mml"] = "text/mathml";
		typemap[".jad"] = "text/vnd.sun.j2me.app-descriptor";
		typemap[".wml"] = "text/vnd.wap.wml";
		typemap[".htc"] = "text/x-component";

		//image
		typemap[".jpg"] = "image/jpeg";
		typemap[".jpeg"] = "image/jpeg";
		typemap[".gif"] = "image/gif";
		typemap[".avif"] = "image/avif";
		typemap[".png"] = "image/png";
		typemap[".svg"] = "image/svg+xml";
		typemap[".svgz"] = "image/svg+xml";
		typemap[".tif"] = "image/tiff";
		typemap[".tiff"] = "image/tiff";
		typemap[".wbmp"] = "image/vnd.wap.wbmp";
		typemap[".webp"] = "image/webp";
		typemap[".ico"] = "image/x-icon";
		typemap[".jng"] = "image/x-jng";
		typemap[".bmp"] = "image/x-ms-bmp";

		//font
		typemap[".woff"] = "font/woff";
		typemap[".woff2"] = "font/woff2";

		//application
		typemap[".js"] = "application/javascript";
		typemap[".atom"] = "application/atom+xml";
		typemap[".rss"] = "application/rss+xml";
		typemap[".jar"] = "application/java-archive";
		typemap[".war"] = "application/java-archive";
		typemap[".ear"] = "application/java-archive";
		typemap[".json"] = "application/json";
		typemap[".hqx"] = "application/mac-binhex40";
		typemap[".doc"] = "application/msword";
		typemap[".pdf"] = "application/pdf";
		typemap[".ps"] = "application/postscript";
		typemap[".eps"] = "application/postscript";
		typemap[".ai"] = "application/postscript";
		typemap[".rtf"] = "application/rtf";
		typemap[".m3u8"] = "application/vnd.apple.mpegurl";
		typemap[".kml"] = "application/vnd.google-earth.kml+xml";
		typemap[".kmz"] = "application/vnd.google-earth.kmz";
		typemap[".xls"] = "application/vnd.ms-excel";
		typemap[".eot"] = "application/vnd.ms-fontobject";
		typemap[".ppt"] = "application/vnd.ms-powerpoint";
		typemap[".odg"] = "application/vnd.oasis.opendocument.graphics";
		typemap[".odp"] = "application/vnd.oasis.opendocument.presentation";
		typemap[".ods"] = "application/vnd.oasis.opendocument.spreadsheet";
		typemap[".odt"] = "application/vnd.oasis.opendocument.text";
		typemap[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
		typemap[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
		typemap[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
		typemap[".wmlc"] = "application/vnd.wap.wmlc";
		typemap[".wasm"] = "application/wasm";
		typemap[".7z"] = "application/x-7z-compressed";
		typemap[".cco"] = "application/x-cocoa";
		typemap[".jardiff"] = "application/x-java-archive-diff";
		typemap[".jnlp"] = "application/x-java-jnlp-file";
		typemap[".run"] = "application/x-makeself";
		typemap[".pl"] = "application/x-perl";
		typemap[".pm"] = "application/x-perl";
		typemap[".pdb"] = "application/x-pilot";
		typemap[".prc"] = "application/x-pilot";
		typemap[".rar"] = "application/x-rar-compressed";
		typemap[".rpm"] = "application/x-redhat-package-manager";
		typemap[".sea"] = "application/x-sea";
		typemap[".swf"] = "application/x-shockwave-flash";
		typemap[".sit"] = "application/x-stuffit";
		typemap[".tcl"] = "application/x-tcl";
		typemap[".tk"] = "application/x-tcl";
		typemap[".der"] = "application/x-x509-ca-cert";
		typemap[".pem"] = "application/x-x509-ca-cert";
		typemap[".crt"] = "application/x-x509-ca-cert";
		typemap[".xpi"] = "application/x-xpinstall";
		typemap[".xhtml"] = "application/xhtml+xml";
		typemap[".xspf"] = "application/xspf+xml";
		typemap[".zip"] = "application/zip";
		typemap[".bin"] = "application/octet-stream";
		typemap[".exe"] = "application/octet-stream";
		typemap[".dll"] = "application/octet-stream";
		typemap[".deb"] = "application/octet-stream";
		typemap[".dmg"] = "application/octet-stream";
		typemap[".iso"] = "application/octet-stream";
		typemap[".img"] = "application/octet-stream";
		typemap[".msm"] = "application/octet-stream";
		typemap[".msp"] = "application/octet-stream";
		typemap[".msm"] = "application/octet-stream";

		//audio
		typemap[".mid"] = "audio/midi";
		typemap[".midi"] = "audio/midi";
		typemap[".kar"] = "audio/midi";
		typemap[".mp3"] = "audio/mpeg";
		typemap[".ogg"] = "audio/ogg";
		typemap[".m4a"] = "audio/x-m4a";
		typemap[".ra"] = "audio/x-realaudio";

		//video
		typemap[".3gpp"] = "video/3gpp";
		typemap[".3gp"] = "video/3gpp";
		typemap[".ts"] = "video/mp2t";
		typemap[".mp4"] = "video/mp4";
		typemap[".mpg"] = "video/mpeg";
		typemap[".mpeg"] = "video/mpeg";
		typemap[".mov"] = "video/quicktime";
		typemap[".webm"] = "video/webm";
		typemap[".flv"] = "video/x-flv";
		typemap[".m4v"] = "video/x-m4v";
		typemap[".mng"] = "video/x-mng";
		typemap[".asx"] = "video/x-ms-asf";
		typemap[".asf"] = "video/x-ms-asf";
		typemap[".wmv"] = "video/x-ms-wmv";
		typemap[".avi"] = "video/x-msvideo";
		typemap[".avi"] = "video/x-msvideo0";
		return (typemap);
	}
	catch (...) {
		std::cerr << "\e[0;31m" << "Fatal error: Failed to init typemap" << "\e[0m" << endl;
		exit(EXIT_FAILURE);
	}
}
