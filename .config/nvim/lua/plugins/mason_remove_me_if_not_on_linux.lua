--mason only has binaries built for linux and macos thusfor, on systems such as any BSD: 
--remove this file and install any LSP servers manualy.

return {
	{
		"williamboman/mason.nvim",
		config = function()
			require("mason").setup()
		end
	},
	{
		"williamboman/mason-lspconfig.nvim",
		config = function()
			require("mason-lspconfig").setup({
				ensure_installed = { "lua_ls" }
			})
		end
	}
}
