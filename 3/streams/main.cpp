#include "stdafx.h"
#include "Compressors.h"
#include "Cryptors.h"
#include "FileStreams.h"

using namespace std;
namespace opt = boost::program_options;

const char* PAR_IN = "in";
const char* PAR_OUT = "out";
const char* PAR_COMPRESS = "compress";
const char* PAR_DECOMPRESS = "decompress";
const char* PAR_ENCRYPT = "encrypt";
const char* PAR_DECRYPT = "decrypt";

opt::options_description InitializeDescription()
{
	opt::options_description desc("All options");
	desc.add_options()
		("in,i", opt::value<string>(), "input file")
		("out,o", opt::value<string>(), "output file")
		(PAR_COMPRESS, "compress input")
		(PAR_DECOMPRESS, "decompress input")
		(PAR_ENCRYPT, opt::value<unsigned int>(), "encrypt with key")
		(PAR_DECRYPT, opt::value<unsigned int>(), "decrypt with key")
		("help,h", "produce help message");
	return desc;
}

opt::variables_map ParseCommandLine(int argc, char *argv[], const opt::options_description& desc)
{
	opt::variables_map vm;
	try
	{
		opt::store(opt::parse_command_line(argc, argv, desc), vm);		opt::notify(vm);
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();
		exit(1);
	}

	if ((argc == 1) || (vm.count("help") > 0))
	{
		std::cout << desc << "\n";
		exit(1);
	}

	if ((vm.count(PAR_OUT) == 0) || (vm.count(PAR_IN) == 0))
	{
		std::cerr << "in and out parameters are required\n";
		exit(1);
	}
	return vm;
}

int main(int argc, char *argv[])
{
	const opt::options_description desc = InitializeDescription();
	const opt::variables_map vm = ParseCommandLine(argc, argv, desc);

	string inFile = vm["in"].as<string>();
	string outFile = vm["out"].as<string>();

	try
	{
		std::stack<IInputDataStreamUniquePtr> inStreams;
		inStreams.push(std::make_unique<CFileInputStream>(inFile));
		std::stack<IOutputDataStreamUniquePtr> outStreams;
		outStreams.push(std::make_unique<CFileOutputStream>(outFile));

		for (const auto& var : vm)
		{
			const auto& param = var.first;
			if (param == PAR_ENCRYPT)
			{
				const unsigned int key = var.second.as<unsigned int>();
				outStreams.push(make_unique<CEncryptor>(*outStreams.top().get(), key));
			}
			else if (param == PAR_DECRYPT)
			{
				const unsigned int key = var.second.as<unsigned int>();
				inStreams.push(make_unique<CDecryptor>(*inStreams.top().get(), key));
			}
			else if (param == PAR_COMPRESS)
			{
				outStreams.push(make_unique<CRleCompressStream>(*outStreams.top().get()));
			}
			else if (param == PAR_DECOMPRESS)
			{
				inStreams.push(make_unique<CRleDecompressStream>(*inStreams.top().get()));
			}
		}

		IInputDataStream* topInputStream = inStreams.top().get();
		IOutputDataStream* topOutputStream = outStreams.top().get();
		while (!topInputStream->IsEOF())
		{
			topOutputStream->WriteByte(topInputStream->ReadByte());
		}
		topOutputStream->Flush();
	}
	catch (const std::exception& e)
	{
		cerr << e.what();
	}
	return 0;
}