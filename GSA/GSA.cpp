#include "GSA.h"

void singleGSA(unsigned regSize, unsigned index) {
	if (index > regSize)
		throw "Invalid target index.";
	if (!(regSize && !(regSize & (regSize - 1))))
		throw "Invalid register size.\nMust be power of 2.";
	if (regSize > (unsigned)pow(2, MAX_QUBITS))
		throw "Invalid register size.\nQubits limit exceeded.";

	srand((unsigned)time(NULL));
	index = (index == 0) ? rand() % regSize + 1 : index;

	Qubit reg((unsigned)log2((double)regSize));

	Matrix query(regSize, regSize);
	for (unsigned i = 0; i < regSize; i++)
		query(i, i) = std::complex<double>(-1, 0) + std::complex<double>(2, 0) * (std::complex<double>)(i != index - 1);

	Matrix diffusion(regSize, regSize, std::complex<double>(2.0 / regSize, 0));
	for (unsigned i = 0; i < regSize; i++)
		diffusion(i, i) -= 1;

	for (unsigned i = 0; i < (unsigned)floor(M_PI / 4 * sqrt((double)regSize)); i++) {
		reg *= query;
		reg *= diffusion;
	}

	std::cout << "Qubit register:\n" << reg;
	std::cout << "Probabilities:\n";
	reg.printProbabilities();
	std::cout << "\nTarget index: " << index << "\n";
}

void multipleGSA(unsigned regSize, std::set<unsigned> indices) {
	for (unsigned i : indices)
		if (i > regSize || i == 0)
			throw "Invalid target index.";
	if (!(regSize && !(regSize & (regSize - 1))))
		throw "Invalid register size.\nMust be power of 2.";
	if (regSize > (unsigned)pow(2, MAX_QUBITS))
		throw "Invalid register size.\nQubits limit exceeded.";

	srand((unsigned)time(NULL));
	if (!indices.size()) {
		unsigned indecesNum = rand() % (regSize / 2) + 1;
		for (unsigned i = 0; i < indecesNum; i++)
			indices.insert(rand() % regSize + 1);
	}
	Qubit reg((unsigned)log2((double)regSize));

	Matrix query(regSize, regSize);
	for (unsigned i = 0; i < regSize; i++) {
		query(i, i) = std::complex<double>(1, 0);
		for (unsigned j : indices)
			if (i == j - 1) {
				query(i, i) = std::complex<double>(-1, 0);
				break;
			}
	}

	Matrix diffusion(regSize, regSize, std::complex<double>(2.0 / regSize, 0));
	for (unsigned i = 0; i < regSize; i++)
		diffusion(i, i) -= 1;

	for (unsigned i = 0; i < (unsigned)floor(M_PI / 4 * sqrt((double)regSize / (double)indices.size()) - 0.5); i++) {
		reg *= query;
		reg *= diffusion;
	}

	std::cout << "Qubit register:\n" << reg;
	std::cout << "Probabilities:\n";
	reg.printProbabilities();
	std::cout << "\nTarget indeces:";
	for (unsigned i : indices)
		std::cout << " " << i;
	std::cout << "\n";
}

int main() {
	try {
		singleGSA(8);
		// or uncomment multipleGSA
		// multipleGSA(8, {1, 7});
	}
	catch (const char* msg) {
		std::cout << msg << "\n";
	}

	return 0;
}
